
#if __cplusplus < 201703L
  #error expects C++17 standard.
#endif


#include <math.h>

#include "../lib/core/keyboard.hpp"
#include "../lib/runtime/window.hpp"
#include "../lib/runtime/application.hpp"
#include "../lib/runtime/data/view.hpp"
#include "../lib/runtime/data/angle.hpp"
#include "../lib/runtime/data/position.hpp"
#include "../lib/scene.hpp"

#include "./lib/bullet.hpp"
#include "./lib/background00.hpp"
#include "./lib/foreground00.hpp"
#include "./lib/player.hpp"
#include "./lib/asteroid00.hpp"


const unsigned long int SCREEN_WIDTH = 1200;
const unsigned long int SCREEN_HEIGHT = 800;

void* quitCallback(void* inp, void* dataOne, void* dataTwo) {
  ApplicationEventParams* parsedInp = reinterpret_cast<ApplicationEventParams*>(inp);

  printf("\n[%u] exiting application at %ldms\n", SDL_GetTicks(), parsedInp->timestamp);

  return (void*)NULL;
}

void* closedCallback(void* inp, void* dataOne, void* dataTwo) {
  WindowEventParams* parsedInp = reinterpret_cast<WindowEventParams*>(inp);

  printf("\n[%u] window closed at %ldms", SDL_GetTicks(), parsedInp->timestamp);

  return (void*)NULL;
}

//void* keyboardCallback(void* inp, void* dataOne, void* dataTwo) {
//  KeyboardEventParams* parsedInp = reinterpret_cast<KeyboardEventParams*>(inp);
//  Player* player = reinterpret_cast<Player*>(dataOne);
//
//  return (void*)NULL;
//}

//void* windowPresentCallback(void* inp, void* dataOne, void* dataTwo) {
//  UserEventParams* parsedInp = reinterpret_cast<UserEventParams*>(inp);
//  Window* win = reinterpret_cast<Window*>(data);
//
//  SDL_RenderPresent(win->getRenderer());
//  //printf("\n[%u] RENDERING!!!!", SDL_GetTicks());
//
//  return (void*)NULL;
//}

//void* sceneEvaluateCallback(void* inp, void* dataOne, void* dataTwo) {
//  Scene* scene = reinterpret_cast<Scene*>(inp);
//
//  Background00* background00 = (Background00*)scene->getElement("background00");
//  Foreground00* foreground00 = (Foreground00*)scene->getElement("foreground00");
//
//  return (void*)NULL;
//}

int main(int argc, char *argv[]) {
  unsigned long int loadStartTimestamp = SDL_GetTicks();

  KeyboardInput::initialize();
  Event::initialize();

  Window* win = new Window();
  Application* app = new Application();
  Scene* scene = new Scene();

  Player* player = Player::loadAssets(scene);
  Background00* background00 = Background00::loadAssets(scene);
  Foreground00* foreground00 = Foreground00::loadAssets(scene);

  //app->on("KEYBOARD", keyboardCallback, (void*)player);
  app->on("QUIT", quitCallback, (void*)NULL);
  win->on("CLOSED", closedCallback, (void*)NULL);
  //win->on("PRESENT", windowPresentCallback, (void*)win);

  scene->view->size.horz = SCREEN_WIDTH;
  scene->view->size.vert = SCREEN_HEIGHT;

  //scene->onEvaluate(sceneEvaluateCallback, (void*)NULL);

  scene->size->horz = 3000;
  scene->size->vert = 1688;

  scene->addBackground("background00", background00);
  scene->addForeground("foreground00", foreground00);
  scene->addElement("player", player);

  for (unsigned long int asteroidIdx = 0; asteroidIdx < Asteroid00::MAX_COUNT; asteroidIdx++) {
    Asteroid00* asteroid = Asteroid00::loadAssets(scene);

    char* name = new char();

    sprintf(name, "asteroid-%lu", asteroid->getIdentifier());

    scene->addElement(name, asteroid);
  }

  for (unsigned long int bulletsIdx = 0; bulletsIdx < Bullet::MAX_COUNT; bulletsIdx++) {
    Bullet* bullet = Bullet::loadAssets(scene);

    char* name = new char();

    sprintf(name, "bullet-%.2lu", bulletsIdx);

    scene->addElement(name, bullet);
  }

  Position* playerAbsolutePos = (Position*)player->state->get("absolute_position");

  playerAbsolutePos->horz = scene->size->horz / 2;
  playerAbsolutePos->vert = scene->size->vert / 2;

  scene->view->position.horz = round((scene->size->horz / 2) - (scene->view->size.horz / 2));
  scene->view->position.vert = round((scene->size->vert / 2) - (scene->view->size.vert / 2));

  win->open("blasteroids", 600, 150, SCREEN_WIDTH, SCREEN_HEIGHT);

  SDL_Renderer* renderer = win->getRenderer();

  app->start();

  unsigned long int frameElapsed = 0;

  unsigned long int frameStart = 0;
  unsigned long int framePasses = 0;
  unsigned long int frameEvalDelay = 100;

  printf("\n[%u] load time: %lums", SDL_GetTicks(), SDL_GetTicks() - loadStartTimestamp);

  while (app->isActive) {
    frameStart = SDL_GetTicks();

    Event::evaluate();

    win->clear();

    scene->evaluate();
    scene->render(renderer);

    frameElapsed += SDL_GetTicks() - frameStart;
    framePasses++;

    win->render();

    if (framePasses % frameEvalDelay == 0) {
      float avgFrameTime = (float)frameElapsed / (float)framePasses;

      printf("\n[%u] average frame time: %.2fms", SDL_GetTicks(), avgFrameTime);

      frameElapsed = 0;
      framePasses = 0;
    }

  }

  Event::deinitialize();
  KeyboardInput::deinitialize();

  delete scene;

  delete win;
  delete app;
}
