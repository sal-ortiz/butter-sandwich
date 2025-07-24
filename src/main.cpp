
#if __cplusplus < 201703L
  #error expects C++17 standard.
#endif


#include <math.h>

#include <core/keyboard.hpp>
#include <core/renderer.hpp>
#include <runtime/window.hpp>
#include <runtime/application.hpp>
#include <runtime/data/view.hpp>
#include <runtime/data/angle.hpp>
#include <runtime/data/position.hpp>
#include <scene.hpp>
#include <tools/logger.hpp>

#include "./lib/bullet.hpp"
#include "./lib/background00.hpp"
#include "./lib/foreground00.hpp"
#include "./lib/player.hpp"
#include "./lib/asteroid00.hpp"


const uint32_t SCREEN_WIDTH = 1200;
const uint32_t SCREEN_HEIGHT = 800;


//void* collisionCallback(void* inp, void* dataOne, void* dataTwo) {
//  //Scene* scene = reinterpret_cast<Scene>(inp);
//
//  printf("\nalfksjdlas;dkfjasl;dfjas;lkfjdas;l\n");
//
//  return (void*)NULL;
//}

//void* quitCallback(LinkedList<void*>* inp) {
void* quitCallback(Application* app) {
  //printf("\n[%u] exiting application\n", SDL_GetTicks());
  Logger::print("exiting application");

  return (void*)NULL;
}

void* closedCallback(Window* win, uint32_t horzPos, uint32_t vertPos) {
  //printf("\n[%u] window closed", SDL_GetTicks());
  Logger::print("window closed");

  return (void*)NULL;
}

//void* keyboardCallback(void* inp, void* dataOne, void* dataTwo) {
//  KeyboardEventParams* parsedInp = reinterpret_cast<KeyboardEventParams*>(inp);
//  Player* player = reinterpret_cast<Player*>(dataOne);
//
//  //if (KeyboardInput::isPressed(44)) {
//  //  printf("\nSPACE PRESSED!!!!!!!!!!!!!");
//  //} else if (KeyboardInput::isHeld(44)) {
//  //  printf("\nSPACE HELD!!!!!!!!!!!!!!!!");
//  //} else if (KeyboardInput::isReleased(44)) {
//  //  printf("\nSPACE RELEASED!!!!!!!!!!!!");
//  //}
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
  uint32_t loadStartTimestamp = SDL_GetTicks();

  KeyboardInput::initialize();
  Event::initialize();
  Hook::initialize();

  Window* win = new Window();
  Application* app = new Application();
  Scene* scene = new Scene();

  Player* player = Player::loadAssets(scene);
  Background00* background00 = Background00::loadAssets(scene);
  Foreground00* foreground00 = Foreground00::loadAssets(scene);

  //app->on("KEYBOARD", keyboardCallback, (void*)player);
  app->on("QUIT", quitCallback);
  win->on("CLOSED", closedCallback);
  //win->on("PRESENT", windowPresentCallback, (void*)win);

  scene->view->size->horz = SCREEN_WIDTH;
  scene->view->size->vert = SCREEN_HEIGHT;

  //scene->onEvaluate(sceneEvaluateCallback, (void*)NULL);

  scene->size->horz = 3000;
  scene->size->vert = 1688;

  scene->addBackground("background00", background00);
  scene->addForeground("foreground00", foreground00);
  scene->addElement("player", player);

  for (uint32_t asteroidIdx = 0; asteroidIdx < Asteroid00::MAX_COUNT; asteroidIdx++) {
    Asteroid00* asteroid = Asteroid00::loadAssets(scene);

    char* name = new char[12];

    sprintf(name, "asteroid-%.2u", asteroid->getIdentifier());

    scene->addElement(name, asteroid);

    delete name;
  }

  for (uint32_t bulletsIdx = 0; bulletsIdx < Bullet::MAX_COUNT; bulletsIdx++) {
    Bullet* bullet = Bullet::loadAssets(scene);

    char* name = new char[10];

    sprintf(name, "bullet-%.2u", bulletsIdx);

    scene->addElement(name, bullet);

    delete name;
  }

  Position* playerAbsolutePos = (Position*)player->state->get("absolute_position");

  playerAbsolutePos->horz = scene->size->horz / 2;
  playerAbsolutePos->vert = scene->size->vert / 2;

  scene->view->position->horz = round((scene->size->horz / 2) - (scene->view->size->horz / 2));
  scene->view->position->vert = round((scene->size->vert / 2) - (scene->view->size->vert / 2));

  win->open("blasteroids", 600, 150, SCREEN_WIDTH, SCREEN_HEIGHT);

  Renderer* renderer = win->getRenderer();

  app->start();

  uint32_t frameElapsed = 0;

  uint32_t frameStart = 0;
  uint32_t framePasses = 0;
  uint32_t frameEvalDelay = 250;

  Logger::print("load time: %ums", SDL_GetTicks(), SDL_GetTicks() - loadStartTimestamp);

  while (app->isActive) {
    frameStart = SDL_GetTicks();

    Event::evaluate();

    scene->evaluate();

    //win->clear();

    scene->render(renderer);

    frameElapsed += SDL_GetTicks() - frameStart;
    framePasses++;

    if (framePasses % frameEvalDelay == 0) {
      float avgFrameTime = (float)frameElapsed / (float)framePasses;

      Logger::print("average frame time: %.2fms", SDL_GetTicks(), avgFrameTime);

      frameElapsed = 0;
      framePasses = 0;
    }

    win->render();
  }

  Hook::deinitialize();
  Event::deinitialize();
  KeyboardInput::deinitialize();

  delete scene;

  delete win;
  delete app;
}
