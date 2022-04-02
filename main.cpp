
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "./lib/runtime/window.hpp"
#include "./lib/runtime/application.hpp"
#include "./lib/core/image.hpp"
#include "./lib/runtime/sprite.hpp"

#include "./lib/scene/character.hpp"

#include "./src/main.hpp"


Window* win = new Window();
Application* app = new Application();

//SceneCharacter* character = new SceneCharacter();
PlayerOne* player = new PlayerOne();



void* quitCallback(void* inp, void* data) {
  ApplicationEventParams* parsedInp = reinterpret_cast<ApplicationEventParams*>(inp);

  printf("Quitting application at %lums\n", parsedInp->timestamp);

  return (void*)NULL;
}

void* closedCallback(void* inp, void* data) {
  WindowEventParams* parsedInp = reinterpret_cast<WindowEventParams*>(inp);

  printf("Window closed at %ldms\n", parsedInp->timestamp);

  return (void*)NULL;
}

void* keyboardCallback(void* inp, void* data) {
  KeyboardEventParams* parsedInp = reinterpret_cast<KeyboardEventParams*>(inp);
  PlayerOne* player = reinterpret_cast<PlayerOne*>(data);

  if ((parsedInp->scanCode == 80) && (parsedInp->state == SDL_PRESSED)) {
    // turn left
    //player->angle->pitch -= 1;
    player->trajectory->angle.pitch -= 5;
  } else if ((parsedInp->scanCode == 79) && (parsedInp->state == SDL_PRESSED)) {
    // turn right
    //player->angle->pitch += 1;
    player->trajectory->angle.pitch += 5;
  } else if ((parsedInp->scanCode == 81) && (parsedInp->state == SDL_PRESSED)) {
    // move forward
    player->trajectory->position.horz += 5;
  }

  //if (parsedInp->state == SDL_PRESSED) {
  //  printf("Key %lu key %s at %lums\n", parsedInp->scanCode, "pressed", parsedInp->timestamp);
  //} else if (parsedInp->state == SDL_RELEASED) {
  //  printf("Key %lu key %s at %lums\n", parsedInp->scanCode, "released", parsedInp->timestamp);
  //}

  return (void*)NULL;
}

int main(int argc, char *argv[]) {
  app->on("KEYBOARD", keyboardCallback, (void*)player);
  app->on("QUIT", quitCallback, (void*)NULL);
  win->on("CLOSED", closedCallback, (void*)NULL);

  Sprite* sprite = new Sprite();

  win->open("The window!", 150, 150, 640, 480);

  Image* shipMovingForward = Image::load("./ship_sheet.bmp", 90, 50, 75, 75);
  Image* shipStandingStill = Image::load("./ship_sheet.bmp", 390, 150, 75, 75);

  sprite->addFrame(shipStandingStill, 0);
  //sprite->addFrame(imgOne, 0);
  //sprite->addFrame(imgTwo, 150);
  sprite->addFrame(200);

  sprite->setLoop(false);

  player->addSprite("standing_still", sprite);
  player->setAction("standing_still");

  player->angle->center.horz = 43;
  player->angle->center.vert = 43;

  app->start();

  unsigned long int numLoops = 0;
  float start = 0.0;
  float elapsed = 0.0;

  while (app->isActive) {
    start = (float)SDL_GetTicks();

    win->clear();

    Event::evaluate();

    player->render(win->getRenderer());
    player->evaluate();

    win->render();

    elapsed += (float)SDL_GetTicks() - start;

    if ((++numLoops % 1000) == 0) {
      printf("\naverage frame time: %fms\n\n", elapsed / numLoops);
    }

  }

  //SDL_Delay(5000);

  delete app;
  delete win;

  SDL_Quit();
}
