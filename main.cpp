
#if __cplusplus < 201703L
  #error expects C++17 standard.
#endif


#include <math.h>

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
    player->trajectory->angle.pitch -= 2;
  }

  if (KeyboardInput::isPressed(79)) {
    // turn right.
    player->setAction("turning_right");
    player->trajectory->angle.pitch += 2;

  }




  unsigned long int horzLowerBorder = round((background->view->size.horz / 2) - (player->width / 2));
  unsigned long int horzUpperBorder = round(background->width - horzLowerBorder);
  unsigned long int vertLowerBorder = round((background->view->size.vert / 2) - (player->height / 2));
  unsigned long int vertUpperBorder = round(background->height - vertLowerBorder);

  if (background->view->position.horz < 0) {
    // keep us from moving beyond our left limit.
    background->view->position.horz = 0;
  }

  //if (background->view->position.vert < 0) {
  //  // keep us from moving beyond our upper limit.
  //  background->view->position.vert = 0;
  //}



  if (KeyboardInput::isPressed(82)) {
    // move forward.
    player->setAction("moving_forward");

    if (background->view->position.horz <= 0) {
      // move our player sprite horizontally along our borders.
      player->trajectory->position.horz += 4 * horzRatio;
      background->view->position.horz = 0;

      if (player->position->horz >= horzLowerBorder && player->trajectory->position.horz > 0) {
        background->trajectory->position.horz = player->trajectory->position.horz;
        player->position->horz = horzLowerBorder;
        player->trajectory->position.horz = 0;
      }

    } else {
      // move our background horizontally around our player.
      background->trajectory->position.horz += 4 * horzRatio;
    }


    if (background->view->position.vert <= 0) {
      // move our player sprite vertically along our borders.
      player->trajectory->position.vert += 4 * vertRatio;
      background->view->position.vert = 0;

      if (player->position->vert >= vertLowerBorder && player->trajectory->position.vert > 0) {
        background->trajectory->position.vert = player->trajectory->position.vert;
        player->position->vert = vertLowerBorder;
        player->trajectory->position.vert = 0;
      }

    } else {
      // move our background vertically around our player.
      background->trajectory->position.vert += 4 * vertRatio;
    }







    if (background->view->position.horz == 0
      && player->position->horz == horzLowerBorder
      && player->trajectory->position.horz < 0
    ) {
      // transfer our background horizontal trajectory to our player.
      player->trajectory->position.horz = background->trajectory->position.horz;
      background->view->position.horz = 0;
      background->trajectory->position.horz = 0;
    }


    if (background->view->position.vert == 0
      && player->position->vert == vertLowerBorder
      && player->trajectory->position.vert < 0
    ) {
      // transfer our background vertical trajectory to our player.
      player->trajectory->position.vert = background->trajectory->position.vert;
      background->view->position.vert = 0;
      background->trajectory->position.vert = 0;
    }




    //printf("\n===========================\n");
    //printf("CLOCK: %d\n", SDL_GetTicks());
    //printf("\n");
    //printf("BORDER: %d\n", horzLowerBorder);
    //printf("SHIP HORZ POS: %f\n", player->position->horz);
    //printf("SHIP VERT POS: %f\n", player->position->vert);
    //printf("SHIP HORZ TRAJ: %f\n", player->trajectory->position.horz);
    //printf("SHIP VERT TRAJ: %f\n", player->trajectory->position.vert);
    //printf("\n");
    //printf("BACKGROUND VIEW HORZ SIZE: %f\n", background->view->size.horz);
    //printf("BACKGROUND VIEW VERT SIZE: %f\n", background->view->size.vert);
    //printf("BACKGROUND VIEW HORZ POS: %f\n", background->view->position.horz);
    //printf("BACKGROUND VIEW VERT POS: %f\n", background->view->position.vert);
    //printf("BACKGROUND VIEW HORZ TRAJ: %f\n", background->trajectory->position.horz);
    //printf("BACKGROUND VIEW VERT TRAJ: %f\n", background->trajectory->position.vert);
    //printf("===========================\n\n");




















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

  player->position->horz = round((SCREEN_WIDTH / 2) - (player->width / 2));
  player->position->vert = round((SCREEN_HEIGHT / 2) - (player->height / 2));


  player->angle->center.horz = 43;
  player->angle->center.vert = 43;

  background->view->size.horz = SCREEN_WIDTH;
  background->view->size.vert = SCREEN_HEIGHT;
  background->view->position.horz = round((background->width / 2) - (SCREEN_WIDTH / 2));
  background->view->position.vert = round((background->height / 2) - (SCREEN_HEIGHT / 2));



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
