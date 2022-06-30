
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "./lib/core/image.hpp"
#include "./lib/core/keyboard.hpp"

#include "./lib/runtime/window.hpp"
#include "./lib/runtime/application.hpp"
#include "./lib/runtime/sprite.hpp"

#include "./src/lib/player_one.hpp"
#include "./lib/scene/background.hpp"


const unsigned char FRAMERATE = 60; // fps
const unsigned int SCREEN_WIDTH = 1024;
const unsigned int SCREEN_HEIGHT = 769;

Window* win = new Window();
Application* app = new Application();

PlayerOne* player = new PlayerOne();
SceneBackground* background = new SceneBackground();


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

//void* keyboardCallback(void* inp, void* data) {
//  PlayerOne* player = reinterpret_cast<PlayerOne*>(data);
//  const unsigned char* keyboardState = SDL_GetKeyboardState(NULL);
//
//  //float horzRatio = 1.0;
//  //float vertRatio = 0.0;
//
//  //if (player->angle->pitch >= 180) {
//  //  horzRatio = -(((270 - player->angle->pitch) / 90));
//  //} else {
//  //  horzRatio = ((90 - player->angle->pitch) / 90);
//  //}
//
//  //if (player->angle->pitch <= 90) {
//  //  vertRatio = (player->angle->pitch) / 90;
//  //} else if (player->angle->pitch > 270) {
//  //  vertRatio = -(360 - player->angle->pitch) / 90;
//  //} else {
//  //  vertRatio = (180 - player->angle->pitch) / 90;
//  //}
//
//  //if (keyboardState[80]) {
//  //  // turn left.
//  //  player->setAction("turning_left");
//  //  player->trajectory->angle.pitch -= 1;
//  //}
//
//  //if (keyboardState[79]) {
//  //  // turn right.
//  //  player->setAction("turning_right");
//  //  player->trajectory->angle.pitch += 1;
//  //}
//
//  //if (keyboardState[82]) {
//  //  // move forward.
//  //  player->setAction("moving_forward");
//  //  player->trajectory->position.horz += 1 * horzRatio;
//  //  player->trajectory->position.vert += 1 * vertRatio;
//  //}
//
//  //// keep angle within 360 degrees
//  //player->angle->pitch = player->angle->pitch < 0 ? 360 - abs(player->angle->pitch) : player->angle->pitch;
//  //player->angle->pitch = player->angle->pitch >= 360 ? player->angle->pitch / 360 : player->angle->pitch;
//
//  return (void*)NULL;
//}

void* evaluateCallback(void* inp, void* data) {
  PlayerOne* player = reinterpret_cast<PlayerOne*>(inp);
  SceneBackground* background = reinterpret_cast<SceneBackground*>(data);

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

  if (KeyboardInput::isReleased(82)) {
    printf("stopping\n");
    player->setAction("standing_still");
  }

  if (KeyboardInput::isPressed(80)) {
    // turn left.
    player->setAction("turning_left");
    player->trajectory->angle.pitch -= 1;
  }

  if (KeyboardInput::isPressed(79)) {
    // turn right.
    player->setAction("turning_right");
    player->trajectory->angle.pitch += 1;

  }
















  if (KeyboardInput::isPressed(82)) {
    // move forward.
    player->setAction("moving_forward");


    if ((background->view->position.horz <= 0)
      && (player->position->horz <= (background->view->size.horz / 2) - (player->width / 2))
    ) {
      player->trajectory->position.horz += 4 * horzRatio;

      background->trajectory->position.horz = 0;
    } else {
      background->trajectory->position.horz += 4 * horzRatio;

    }

  }


  if ((background->view->position.horz <= 0) //{
    && (player->position->horz > (background->view->size.horz / 2) - (player->width / 2))
  ) {

    if (horzRatio < 0) {
      player->trajectory->position.horz = background->trajectory->position.horz;
      background->trajectory->position.horz = 0;
    } else {
      background->trajectory->position.horz = player->trajectory->position.horz;
      player->trajectory->position.horz = 0;
    }

  }


  if (background->view->position.horz < 0) {
    background->view->position = 0;
  }

  if (player->position->horz < 0) {
    player->position->horz = 0;
  }


  // keep angle within 360 degrees
  player->angle->pitch = player->angle->pitch < 0 ? 360 - abs(player->angle->pitch) : player->angle->pitch;
  player->angle->pitch = player->angle->pitch >= 360 ? player->angle->pitch / 360 : player->angle->pitch;

  return (void*)NULL;
}


int main(int argc, char *argv[]) {
  //app->on("KEYBOARD", keyboardCallback, (void*)player);
  app->on("QUIT", quitCallback, (void*)NULL);
  win->on("CLOSED", closedCallback, (void*)NULL);

  player->onEvaluate(evaluateCallback, (void*)background);

  Sprite* standingStillSprite = new Sprite();
  Sprite* movingForwardSprite = new Sprite();
  Sprite* turningLeftSprite = new Sprite();
  Sprite* turningRightSprite = new Sprite();
  Sprite* backgroundSprite = new Sprite();

  win->open("The window!", 150, 150, SCREEN_WIDTH, SCREEN_HEIGHT);

  Image* shipStandingStill = Image::load("./ship_sheet.bmp", 390, 150, 75, 75);
  Image* shipTurningLeft = Image::load("./ship_sheet.bmp", 490, 50, 75, 75);
  Image* shipTurningRight = Image::load("./ship_sheet.bmp", 190, 50, 75, 75);
  Image* shipMovingForward = Image::load("./ship_sheet.bmp", 90, 50, 75, 75);
  Image* backgroundImage = Image::load("./background.bmp", 0, 0, 3008, 2000);

  standingStillSprite->addFrame(shipStandingStill, 0);
  movingForwardSprite->addFrame(shipMovingForward, 0);
  turningLeftSprite->addFrame(shipTurningLeft, 0);
  turningRightSprite->addFrame(shipTurningRight, 0);
  backgroundSprite->addFrame(backgroundImage, 0);
  //sprite->addFrame(imgOne, 0);
  //sprite->addFrame(imgTwo, 150);
  standingStillSprite->addFrame(200);
  movingForwardSprite->addFrame(200);
  turningLeftSprite->addFrame(200);
  turningRightSprite->addFrame(200);
  backgroundSprite->addFrame(200);

  standingStillSprite->setLoop(false);
  movingForwardSprite->setLoop(false);
  turningLeftSprite->setLoop(false);
  turningRightSprite->setLoop(false);
  backgroundSprite->setLoop(false);

  player->addSprite("standing_still", standingStillSprite);
  player->addSprite("moving_forward", movingForwardSprite);
  player->addSprite("turning_left", turningLeftSprite);
  player->addSprite("turning_right", turningRightSprite);
  player->setAction("standing_still");
  background->addSprite("background", backgroundSprite);
  background->setAction("background");

  player->position->horz = (SCREEN_WIDTH / 2) - (75 / 2);
  player->position->vert = (SCREEN_HEIGHT / 2) - (75 / 2);

  player->angle->center.horz = 43;
  player->angle->center.vert = 43;

  background->view->position.horz = 0;
  background->view->position.vert = 0;
  background->view->size.horz = SCREEN_WIDTH;
  background->view->size.vert = SCREEN_HEIGHT;


  app->start();

  float start = 0.0;
  float elapsed = 0.0;

  const unsigned int frameDelay = 1000 / FRAMERATE;

  while (app->isActive) {
    start = (float)SDL_GetTicks();

    Event::evaluate();
    KeyboardInput::updateState();

    if (elapsed > frameDelay) {

      //win->clear();

      background->render(win->getRenderer());
      background->evaluate();

      player->render(win->getRenderer());
      player->evaluate();

      win->render();

      start = (float)SDL_GetTicks();
      elapsed = 0.0;
    }

    elapsed += (float)SDL_GetTicks() - start;
  }

  //SDL_Delay(5000);

  delete app;
  delete win;

  SDL_Quit();
}
