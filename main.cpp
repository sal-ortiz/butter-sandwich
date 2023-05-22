
#if __cplusplus < 201703L
  #error expects C++17 standard.
#endif


#include <string.h>
#include <math.h>
#include <time.h>

#include "./lib/core/keyboard.hpp"

#include "./lib/runtime/window.hpp"
#include "./lib/runtime/application.hpp"

#include "./lib/runtime/data/view.hpp"
#include "./lib/runtime/data/angle.hpp"
#include "./lib/runtime/data/position.hpp"

#include "./lib/scene.hpp"

#include "./src/lib/bullet.hpp"
#include "./src/lib/background.hpp"
#include "./src/lib/player.hpp"


const unsigned long int SCREEN_WIDTH = 1024;
const unsigned long int SCREEN_HEIGHT = 769;

void* quitCallback(void* inp, void* data) {
  ApplicationEventParams* parsedInp = reinterpret_cast<ApplicationEventParams*>(inp);

  printf("\nQuitting application at %lums\n", parsedInp->timestamp);

  return (void*)NULL;
}

void* closedCallback(void* inp, void* data) {
  WindowEventParams* parsedInp = reinterpret_cast<WindowEventParams*>(inp);

  printf("\nWindow closed at %ldms", parsedInp->timestamp);

  return (void*)NULL;
}

void* keyboardCallback(void* inp, void* data) {
  KeyboardEventParams* parsedInp = reinterpret_cast<KeyboardEventParams*>(inp);
  Player* player = reinterpret_cast<Player*>(data);

  //const unsigned char* keyboardState = SDL_GetKeyboardState(NULL);
  KeyboardInput::updateState();

  return (void*)NULL;
}

//void* windowPresentCallback(void* inp, void* data) {
//  UserEventParams* parsedInp = reinterpret_cast<UserEventParams*>(inp);
//  Window* win = reinterpret_cast<Window*>(data);
//
//  SDL_RenderPresent(win->getRenderer());
//  //printf("\n[%u] RENDERING!!!!", SDL_GetTicks());
//
//  return (void*)NULL;
//}

void* sceneEvaluateCallback(void* inp, void* data) {
  Scene* scene = reinterpret_cast<Scene*>(inp);

  Background* background = (Background*)scene->getElement("background");
  View* backgroundView = (View*)background->state->get("view");

  backgroundView->position.horz = scene->view->position.horz;
  backgroundView->position.vert = scene->view->position.vert;

  // TODO: This only needs to be set once.
  backgroundView->size.horz = scene->view->size.horz;
  backgroundView->size.vert = scene->view->size.vert;

  return (void*)NULL;
}

int main(int argc, char *argv[]) {
  Window* win = new Window();
  Application* app = new Application();
  Scene* scene = new Scene();

  Player* player = Player::loadAssets(scene);
  Background* background = Background::loadAssets(scene);

  scene->size->horz = 3000;
  scene->size->vert = 1688;

  scene->addElement("background", background);
  scene->addElement("player", player);

  for (unsigned long int bulletsIdx = 0; bulletsIdx < Bullet::MAX_COUNT; bulletsIdx++) {
    Bullet* bullet = Bullet::loadAssets(scene);

    char* name = new char();

    sprintf(name, "bullet-%.2lu", bulletsIdx);

    scene->addElement(name, bullet);
  }

  scene->onEvaluate(sceneEvaluateCallback, (void*)NULL);

  app->on("KEYBOARD", keyboardCallback, (void*)player);
  app->on("QUIT", quitCallback, (void*)NULL);
  win->on("CLOSED", closedCallback, (void*)NULL);
  //win->on("PRESENT", windowPresentCallback, (void*)win);

  Angle* playerAngle = (Angle*)player->state->get("angle");

  playerAngle->center.horz = 43;
  playerAngle->center.vert = 43;

  scene->view->size.horz = SCREEN_WIDTH;
  scene->view->size.vert = SCREEN_HEIGHT;

  scene->view->position.horz = round((scene->size->horz / 2) - (scene->view->size.horz / 2));
  scene->view->position.vert = round((scene->size->vert / 2) - (scene->view->size.vert / 2));

  player->state->set("absolute_position", new Position(
    (scene->size->horz / 2) - (scene->view->size.horz / 2) - (player->width / 2),
    (scene->size->vert / 2) - (scene->view->size.vert / 2) - (player->width / 2)
  ));

  background->state->set("absolute_position", new Position());

  Position* playerAbsolutePos = (Position*)player->state->get("absolute_position");

  scene->view->position.horz = playerAbsolutePos->horz - round(scene->view->size.horz / 2);
  scene->view->position.vert = playerAbsolutePos->vert - round(scene->view->size.vert / 2);

  win->open("blasteroids", 600, 150, SCREEN_WIDTH, SCREEN_HEIGHT);

  SDL_Renderer* renderer = win->getRenderer();

  app->start();

  KeyboardInput::updateState();

  unsigned long int frameElapsed = 0;

  unsigned long int frameStart = 0;
  unsigned long int framePasses = 0;
  unsigned long int frameEvalDelay = 100;

  while (app->isActive) {

    Event::evaluate();

    frameStart = SDL_GetTicks();

    //win->clear();

    scene->evaluate();
    scene->render(renderer);


    frameElapsed += SDL_GetTicks() - frameStart;
    framePasses++;

    win->render();

    if (framePasses % frameEvalDelay == 0) {
      float avgFrameTime = (float)frameElapsed / (float)framePasses;

      printf("\n[%u] AVG FRAME TIME: %.2fms", SDL_GetTicks(), avgFrameTime);

      frameElapsed = 0;
      framePasses = 0;
    }

  }

  delete scene;

  delete win;
  delete app;
}
