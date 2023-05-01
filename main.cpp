
#if __cplusplus < 201703L
  #error expects C++17 standard.
#endif


#include <math.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "./lib/core/image.hpp"
#include "./lib/core/keyboard.hpp"

#include "./lib/runtime/window.hpp"
#include "./lib/runtime/application.hpp"
#include "./lib/runtime/sprite.hpp"

#include "./src/lib/player_one.hpp"
#include "./src/lib/background.hpp"
#include "./src/lib/bullet.hpp"


const unsigned long int FRAMERATE = 60; // fps
const unsigned long int SCREEN_WIDTH = 1024;
const unsigned long int SCREEN_HEIGHT = 769;

float playerHorzRatio = 1.0;
float playerVertRatio = 0.0;
float bulletHorzRatio = 1.0;
float bulletVertRatio = 0.0;


Window* win = new Window();
Application* app = new Application();

PlayerOne* player = new PlayerOne();
Background* background = new Background();
Bullet* bullet = new Bullet();



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
  //PlayerOne* player = reinterpret_cast<PlayerOne*>(data);
  const unsigned char* keyboardState = SDL_GetKeyboardState(NULL);

  Trajectory* playerTraj = (Trajectory*)player->state->get("trajectory");
//
//  //float playerHorzRatio = 1.0;
//  //float playerVertRatio = 0.0;
//
//  //if (player->angle->pitch >= 180) {
//  //  playerHorzRatio = -(((270 - player->angle->pitch) / 90));
//  //} else {
//  //  playerHorzRatio = ((90 - player->angle->pitch) / 90);
//  //}
//
//  //if (player->angle->pitch <= 90) {
//  //  playerVertRatio = (player->angle->pitch) / 90;
//  //} else if (player->angle->pitch > 270) {
//  //  playerVertRatio = -(360 - player->angle->pitch) / 90;
//  //} else {
//  //  playerVertRatio = (180 - player->angle->pitch) / 90;
//  //}
//
//  //if (keyboardState[80]) {
//  //  // turn left.
//  //  Trajectory* playerTraj = (Trajectory*)player->state->get("trajectory");
//
//  //  player->setAction("turning_left");
//  //  playerTraj->angle.pitch -= 2;
//  //}
//
//  //if (keyboardState[79]) {
//  //  // turn right.
//  //  Trajectory* playerTraj = (Trajectory*)player->state->get("trajectory");
//
//  //  player->setAction("turning_right");
//  //  playerTraj->angle.pitch += 2;
//  //}
//
  if (keyboardState[82]) {
    //// move forward.
    //player->setAction("moving_forward");
    //playerTraj->position.horz += 1 * playerHorzRatio;
    //playerTraj->position.vert += 1 * playerVertRatio;
  }
//
//  //// keep angle within 360 degrees
//  //player->angle->pitch = player->angle->pitch < 0 ? 360 - abs(player->angle->pitch) : player->angle->pitch;
//  //player->angle->pitch = player->angle->pitch >= 360 ? player->angle->pitch / 360 : player->angle->pitch;
//
  return (void*)NULL;
}



//void* backgroundEvaluateCallback(void* inp, void* data) {
//  PlayerOne* player = reinterpret_cast<PlayerOne*>(inp);
//  SceneBackground* background = reinterpret_cast<SceneBackground*>(data);
//
//  Position* playerPos = (Position*)player->state->get("position");
//  Position* bulletPos = (Position*)bullet->state->get("position");
//  Angle* playerAngle = (Angle*)player->state->get("angle");
//  Trajectory* playerTraj = (Trajectory*)player->state->get("trajectory");
//  Trajectory* backgroundTraj = (Trajectory*)background->state->get("trajectory");
//  View* backgroundView = (View*)background->state->get("view");
//
//  Position* playerAbsolutePos = (Position*)player->state->get("absolute_position");
//
//  return (void*)NULL;
//}


void* playerEvaluateCallback(void* inp, void* data) {
  PlayerOne* player = reinterpret_cast<PlayerOne*>(inp);
  SceneBackground* background = reinterpret_cast<SceneBackground*>(data);

  Position* playerPos = (Position*)player->state->get("position");
  Angle* playerAngle = (Angle*)player->state->get("angle");
  Trajectory* playerTraj = (Trajectory*)player->state->get("trajectory");
  Trajectory* backgroundTraj = (Trajectory*)background->state->get("trajectory");
  View* backgroundView = (View*)background->state->get("view");

  Position* playerAbsolutePos = (Position*)player->state->get("absolute_position");

  if (playerAbsolutePos->horz < round(backgroundView->size.horz / 2)) {
    // move along our left border.
    playerPos->horz = playerAbsolutePos->horz;

  } else if (playerAbsolutePos->horz > (background->width - round(backgroundView->size.horz / 2))){
    // move along our right border.
    playerPos->horz = (unsigned long int)playerAbsolutePos->horz % (unsigned long int)(backgroundView->size.horz - round(player->width / 2));

  } else {
    // move along the center of our map.
    backgroundView->position.horz = playerAbsolutePos->horz - round(backgroundView->size.horz / 2);

    playerPos->horz = round(backgroundView->size.horz / 2);
  }

  if (playerAbsolutePos->vert < round(backgroundView->size.vert / 2)) {
    // move along our upper border.
    playerPos->vert = playerAbsolutePos->vert;

  } else if (playerAbsolutePos->vert > (background->height - round(backgroundView->size.vert / 2))) {
    // move along our lower border.
    playerPos->vert = (unsigned long int)playerAbsolutePos->vert % (unsigned long int)(backgroundView->size.vert - round(player->height / 2));

  } else {
    // move along the center of our map.
    backgroundView->position.vert = playerAbsolutePos->vert - round(backgroundView->size.vert / 2);

    playerPos->vert = round(backgroundView->size.vert / 2);
  }

  if (playerAbsolutePos->horz < 0) {
    playerAbsolutePos->horz = 0;
    playerTraj->position.horz = 0;
  }

  if (playerAbsolutePos->vert < 0) {
    playerAbsolutePos->vert = 0;
    playerTraj->position.vert = 0;
  }

  if (playerAbsolutePos->horz > background->width) {
    playerAbsolutePos->horz = background->width;
    playerTraj->position.horz = 0;
  }

  if (playerAbsolutePos->vert > background->height) {
    playerAbsolutePos->vert = background->height;
    playerTraj->position.vert = 0;
  }


  if (playerAngle->pitch >= 180) {
    playerHorzRatio = -(((270 - playerAngle->pitch) / 90));
  } else {
    playerHorzRatio = ((90 - playerAngle->pitch) / 90);
  }

  if (playerAngle->pitch <= 90) {
    playerVertRatio = (playerAngle->pitch) / 90;
  } else if (playerAngle->pitch > 270) {
    playerVertRatio = -(360 - playerAngle->pitch) / 90;
  } else {
    playerVertRatio = (180 - playerAngle->pitch) / 90;
  }

//  if (KeyboardInput::isReleased(82)) {
//    printf("stopping\n");
//    player->setAction("standing_still");
//  }

  if (KeyboardInput::isPressed(80)) {
    // turn left.
    player->setAction("turning_left");
    playerTraj->angle.pitch -= 2;
  }

  if (KeyboardInput::isPressed(79)) {
    // turn right.
    player->setAction("turning_right");
    playerTraj->angle.pitch += 2;
  }

  if (KeyboardInput::isPressed(82)) {
    // move forward.
    player->setAction("moving_forward");

    playerTraj->position.horz += 4 * playerHorzRatio;
    playerTraj->position.vert += 4 * playerVertRatio;
  }

  // keep angle within 360 degrees
  // TODO: enforce this from a state callback.
  playerAngle->pitch = playerAngle->pitch < 0 ? 360 - abs(playerAngle->pitch) : playerAngle->pitch;
  playerAngle->pitch = playerAngle->pitch >= 360 ? playerAngle->pitch / 360 : playerAngle->pitch;

  return (void*)NULL;
}

void* bulletEvaluateCallback(void* inp, void* data) {
  Bullet* bullet = reinterpret_cast<Bullet*>(inp);
  //PlayerOne* player = reinterpret_cast<PlayerOne*>(data);

  Position* playerPos = (Position*)player->state->get("position");
  Angle* playerAngle = (Angle*)player->state->get("angle");
  Trajectory* playerTraj = (Trajectory*)player->state->get("trajectory");

  Position* playerAbsolutePos = (Position*)player->state->get("absolute_position");
  Position* bulletAbsolutePos = (Position*)bullet->state->get("absolute_position");

  Position* bulletPos = (Position*)bullet->state->get("position");
  Angle* bulletAngle = (Angle*)bullet->state->get("angle");
  Trajectory* bulletTraj = (Trajectory*)bullet->state->get("trajectory");

  View* backgroundView = (View*)background->state->get("view");


  if (KeyboardInput::isPressed(44) && bullet->getVisibility() == false) {
    // fire a pellet

    bulletHorzRatio = playerHorzRatio;
    bulletVertRatio = playerVertRatio;

    bulletTraj->position.horz = 28 * bulletHorzRatio;
    bulletTraj->position.vert = 28 * bulletVertRatio;

    bulletAbsolutePos->horz = playerAbsolutePos->horz + 20;
    bulletAbsolutePos->vert = playerAbsolutePos->vert + 20;

    bulletAngle->pitch = playerAngle->pitch + 132;

    bullet->setVisibility(true);
  }

  if (bulletAbsolutePos->horz > backgroundView->position.horz
    && bulletAbsolutePos->horz < (backgroundView->position.horz + backgroundView->size.horz)
    && bulletAbsolutePos->vert > backgroundView->position.vert
    && bulletAbsolutePos->vert < (backgroundView->position.vert + backgroundView->size.vert)
  ) {
    // our bullet is visible within our screen.
    bulletPos->horz = (bulletAbsolutePos->horz - backgroundView->position.horz);
    bulletPos->vert = (bulletAbsolutePos->vert - backgroundView->position.vert);

  }

  if (bulletAbsolutePos->horz < 0
    || bulletAbsolutePos->vert < 0
    || bulletAbsolutePos->horz > background->width
    || bulletAbsolutePos->vert > background->height
  ) {
    // our bullet has left our space.

    bulletTraj->position.horz = 0;
    bulletTraj->position.vert = 0;

    bulletPos->horz = playerPos->horz + 20;
    bulletPos->vert = playerPos->vert + 20;

    bulletAbsolutePos->horz = playerAbsolutePos->horz + 20;
    bulletAbsolutePos->vert = playerAbsolutePos->vert + 20;

    bullet->setVisibility(0);
  }

  return (void*)NULL;
}


int main(int argc, char *argv[]) {
  app->on("KEYBOARD", keyboardCallback, (void*)player);
  app->on("QUIT", quitCallback, (void*)NULL);
  win->on("CLOSED", closedCallback, (void*)NULL);

  player->onEvaluate(playerEvaluateCallback, (void*)background);
  bullet->onEvaluate(bulletEvaluateCallback, (void*)player);
  //background->onEvaluate(backgroundEvaluateCallback, (void*)player);

  Sprite* bulletSprite = new Sprite();
  Sprite* standingStillSprite = new Sprite();
  Sprite* movingForwardSprite = new Sprite();
  Sprite* turningLeftSprite = new Sprite();
  Sprite* turningRightSprite = new Sprite();
  Sprite* backgroundSprite = new Sprite();


  Image* bulletImage = Image::load("./bullet.bmp", 0, 0, 6, 6);
  Image* shipStandingStill = Image::load("./ship_sheet.bmp", 390, 150, 75, 75);
  Image* shipTurningLeft = Image::load("./ship_sheet.bmp", 490, 50, 75, 75);
  Image* shipTurningRight = Image::load("./ship_sheet.bmp", 190, 50, 75, 75);
  Image* shipMovingForward = Image::load("./ship_sheet.bmp", 90, 50, 75, 75);
  //Image* backgroundImage = Image::load("./background.bmp", 0, 0, 3008, 2000);
  //Image* backgroundImage = Image::load("./background2.bmp", 0, 0, 3840, 1264);
  Image* backgroundImage = Image::load("./background3.bmp", 0, 0, 3000, 1688);

  bulletSprite->addFrame(bulletImage, 0);
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

  bulletSprite->setLoop(false);
  standingStillSprite->setLoop(false);
  movingForwardSprite->setLoop(false);
  turningLeftSprite->setLoop(false);
  turningRightSprite->setLoop(false);
  backgroundSprite->setLoop(false);

  bullet->addSprite("bullet", bulletSprite);
  player->addSprite("standing_still", standingStillSprite);
  player->addSprite("moving_forward", movingForwardSprite);
  player->addSprite("turning_left", turningLeftSprite);
  player->addSprite("turning_right", turningRightSprite);
  background->addSprite("background", backgroundSprite);

  bullet->setAction("bullet");
  player->setAction("standing_still");
  background->setAction("background");

  Position* playerPos = (Position*)player->state->get("position");
  Angle* playerAngle = (Angle*)player->state->get("angle");
  View* backgroundView = (View*)background->state->get("view");

  Position* bulletPos = (Position*)bullet->state->get("position");
  Angle* bulletAngle = (Angle*)bullet->state->get("angle");

  playerAngle->center.horz = 43;
  playerAngle->center.vert = 43;

  backgroundView->size.horz = SCREEN_WIDTH;
  backgroundView->size.vert = SCREEN_HEIGHT;
  backgroundView->position.horz = round((background->width / 2) - (SCREEN_WIDTH / 2));
  backgroundView->position.vert = round((background->height / 2) - (SCREEN_HEIGHT / 2));



  player->state->set("absolute_position", new Position(
    (background->width / 2) - (backgroundView->size.horz / 2) - (player->width / 2),
    (background->height / 2) - (backgroundView->size.vert / 2) - (player->width / 2)
  ));

  bullet->state->set("absolute_position", new Position(
    (background->width / 2) - (backgroundView->size.horz / 2) - (player->width / 2) + 20,
    (background->height / 2) - (backgroundView->size.vert / 2) - (player->width / 2) + 20
  ));

  Position* playerAbsolutePos = (Position*)player->state->get("absolute_position");
  Position* bulletAbsolutePos = (Position*)bullet->state->get("absolute_position");

  backgroundView->position.horz = playerAbsolutePos->horz - round(backgroundView->size.horz / 2);
  backgroundView->position.vert = playerAbsolutePos->vert - round(backgroundView->size.vert / 2);

  bullet->setVisibility(false);

  bulletAngle->center.horz = playerAngle->center.horz - 20;
  bulletAngle->center.vert = playerAngle->center.vert - 20;


  win->open("blasteroids", 600, 150, SCREEN_WIDTH, SCREEN_HEIGHT);

  SDL_Renderer* renderer = win->getRenderer();

  app->start();

  unsigned long int frameElapsed = 0;
  unsigned long int frameDelay = 1000 / FRAMERATE;

  unsigned long int frameStart = 0;
  unsigned long int framePasses = 0;
  unsigned long int frameEvalDelay = 100;

  while (app->isActive) {

    if (frameElapsed == 0 || frameElapsed > frameDelay) {
      frameStart = SDL_GetTicks();

      KeyboardInput::updateState();
      Event::evaluate();

      background->evaluate();
      player->evaluate();
      bullet->evaluate();

      //win->clear();

      background->render(renderer);
      player->render(renderer);
      bullet->render(renderer);

      win->render();

      frameElapsed += SDL_GetTicks() - frameStart;
      framePasses++;

      if (framePasses % frameEvalDelay == 0) {
        float avgFrameTime = (float)frameElapsed / (float)framePasses;

        printf("\n[%u] AVG FRAME TIME: %.2fms per %lu frames", SDL_GetTicks(), avgFrameTime, frameEvalDelay);

        frameElapsed = 0;
        framePasses = 0;
      }


    }

  }

  delete win;
  delete app;
}
