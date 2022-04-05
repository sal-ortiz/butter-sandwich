
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "./lib/runtime/window.hpp"
#include "./lib/runtime/application.hpp"
#include "./lib/core/image.hpp"
#include "./lib/runtime/sprite.hpp"

#include "./src/lib/player_one.hpp"


Window* win = new Window();
Application* app = new Application();

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

  float horzRatio = 1.0;
  float vertRatio = 0.0;


  if (player->angle->pitch >= 180) {
    horzRatio = -(((270 - player->angle->pitch) / 90));
  } else {
    horzRatio = ((90 - player->angle->pitch) / 90);
  }

  if (player->angle->pitch <= 90) {
    vertRatio = (player->angle->pitch) / 90;
  } else if (player->angle->pitch > 270) {
    vertRatio = -(360 - player->angle->pitch) / 90;
  } else {
    vertRatio = (180 - player->angle->pitch) / 90;
  }


  if ((parsedInp->scanCode == 80) && (parsedInp->state == SDL_PRESSED)) {
    // turn left
    player->setAction("turning_left");
    player->trajectory->angle.pitch -= 1;
  } else if ((parsedInp->scanCode == 79) && (parsedInp->state == SDL_PRESSED)) {
    // turn right
    player->setAction("turning_right");
    player->trajectory->angle.pitch += 1;
  } else if ((parsedInp->scanCode == 81) && (parsedInp->state == SDL_PRESSED)) {
    // move backward.
    //player->setAction("moving_backward");
    //player->trajectory->position.horz -= 1;
  } else if ((parsedInp->scanCode == 82) && (parsedInp->state == SDL_PRESSED)) {
    // move forward
    player->setAction("moving_forward");
    player->trajectory->position.horz += 1 * horzRatio;
    player->trajectory->position.vert += 1 * vertRatio;
  }

  // keep angle within 360 degrees
  //player->angle->pitch = (float)((unsigned int)player->angle->pitch % 360);
  player->angle->pitch = player->angle->pitch < 0 ? 360 - abs(player->angle->pitch) : player->angle->pitch;
  player->angle->pitch = player->angle->pitch >= 360 ? player->angle->pitch / 360 : player->angle->pitch;

  if (parsedInp->state == SDL_RELEASED) {
    //printf("\n\n");
    //printf("%f\n", player->angle->pitch);
    //printf("\n\n");

    player->setAction("standing_still");
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

  Sprite* standingStillSprite = new Sprite();
  Sprite* movingForwardSprite = new Sprite();
  Sprite* turningLeftSprite = new Sprite();
  Sprite* turningRightSprite = new Sprite();

  win->open("The window!", 150, 150, 640, 480);

  Image* shipStandingStill = Image::load("./ship_sheet.bmp", 390, 150, 75, 75);
  Image* shipTurningLeft = Image::load("./ship_sheet.bmp", 490, 50, 75, 75);
  Image* shipTurningRight = Image::load("./ship_sheet.bmp", 190, 50, 75, 75);
  Image* shipMovingForward = Image::load("./ship_sheet.bmp", 90, 50, 75, 75);

  standingStillSprite->addFrame(shipStandingStill, 0);
  movingForwardSprite->addFrame(shipMovingForward, 0);
  turningLeftSprite->addFrame(shipTurningLeft, 0);
  turningRightSprite->addFrame(shipTurningRight, 0);
  //sprite->addFrame(imgOne, 0);
  //sprite->addFrame(imgTwo, 150);
  standingStillSprite->addFrame(200);
  movingForwardSprite->addFrame(200);
  turningLeftSprite->addFrame(200);
  turningRightSprite->addFrame(200);

  standingStillSprite->setLoop(false);
  movingForwardSprite->setLoop(false);
  turningLeftSprite->setLoop(false);
  turningRightSprite->setLoop(false);

  player->addSprite("standing_still", standingStillSprite);
  player->addSprite("moving_forward", movingForwardSprite);
  player->addSprite("turning_left", turningLeftSprite);
  player->addSprite("turning_right", turningRightSprite);
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
