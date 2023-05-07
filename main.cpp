
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

#include "./lib/runtime/data/trajectory.hpp"
#include "./lib/runtime/data/view.hpp"
#include "./lib/runtime/data/angle.hpp"
#include "./lib/runtime/data/position.hpp"

#include "./src/lib/player_one.hpp"
#include "./src/lib/background.hpp"
#include "./src/lib/bullet.hpp"


const unsigned long int FRAMERATE = 60; // fps
const unsigned long int SCREEN_WIDTH = 1024;
const unsigned long int SCREEN_HEIGHT = 769;

const unsigned int NUM_BULLETS = 18;
const unsigned int BULLET_DELAY = 200; // ms (TODO: this should be in frames, not time)

float playerHorzRatio = 1.0;
float playerVertRatio = 0.0;
float bulletHorzRatio = playerHorzRatio;
float bulletVertRatio = playerVertRatio;

Dict<Bullet*>* bullets = new Dict<Bullet*>();
Dict<SceneBase*>* sceneElements = new Dict<SceneBase*>();

unsigned int lastBulletTimestamp = 0;


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
  PlayerOne* player = reinterpret_cast<PlayerOne*>(data);

  //const unsigned char* keyboardState = SDL_GetKeyboardState(NULL);

  KeyboardInput::updateState();

  return (void*)NULL;
}

void* backgroundEvaluateCallback(void* inp, void* data) {
  Background* background = reinterpret_cast<Background*>(inp);
  Dict<SceneBase*>* sceneElements = reinterpret_cast<Dict<SceneBase*>*>(data);

  PlayerOne* player = (PlayerOne*)sceneElements->get("player");

  Trajectory* backgroundTraj = (Trajectory*)background->state->get("trajectory");
  View* backgroundView = (View*)background->state->get("view");

  backgroundView->position.horz += backgroundTraj->position.horz;
  backgroundView->position.vert += backgroundTraj->position.vert;
  backgroundView->position.depth += backgroundTraj->position.depth;

  backgroundTraj->position.horz *= backgroundTraj->positionRate.horz;
  backgroundTraj->position.vert *= backgroundTraj->positionRate.vert;
  backgroundTraj->position.depth *= backgroundTraj->positionRate.depth;

  return (void*)NULL;
}

void* bulletEvaluateCallback(void* inp, void* data) {
  Bullet* bullet = reinterpret_cast<Bullet*>(inp);
  Dict<SceneBase*>* sceneElements = reinterpret_cast<Dict<SceneBase*>*>(data);

  PlayerOne* player = (PlayerOne*)sceneElements->get("player");
  Background* background = (Background*)sceneElements->get("background");

  Position* playerPos = (Position*)player->state->get("position");
  Angle* playerAngle = (Angle*)player->state->get("angle");
  Trajectory* playerTraj = (Trajectory*)player->state->get("trajectory");

  Position* playerAbsolutePos = (Position*)player->state->get("absolute_position");
  Position* bulletAbsolutePos = (Position*)bullet->state->get("absolute_position");

  Position* bulletPos = (Position*)bullet->state->get("position");
  Angle* bulletAngle = (Angle*)bullet->state->get("angle");
  Trajectory* bulletTraj = (Trajectory*)bullet->state->get("trajectory");

  View* backgroundView = (View*)background->state->get("view");

  bulletAbsolutePos->horz += bulletTraj->position.horz;
  bulletAbsolutePos->vert += bulletTraj->position.vert;
  bulletAbsolutePos->depth += bulletTraj->position.depth;

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

    unsigned long int identifier = bullet->getIdentifier();
    unsigned long int strLen = (unsigned long int)(ceil(log10(identifier) + 1) * sizeof(char));

    char bulletIdentifier[strLen];

    sprintf(bulletIdentifier, "%lu", identifier);

    bullets->remove(bulletIdentifier);
  }

  return (void*)NULL;
}

void* playerEvaluateCallback(void* inp, void* data) {
  PlayerOne* player = reinterpret_cast<PlayerOne*>(inp);
  Dict<SceneBase*>* sceneElements = reinterpret_cast<Dict<SceneBase*>*>(data);

  Background* background = (Background*)sceneElements->get("background");

  Position* playerPos = (Position*)player->state->get("position");
  Angle* playerAngle = (Angle*)player->state->get("angle");
  Trajectory* playerTraj = (Trajectory*)player->state->get("trajectory");
  Trajectory* backgroundTraj = (Trajectory*)background->state->get("trajectory");
  View* backgroundView = (View*)background->state->get("view");

  Position* playerAbsolutePos = (Position*)player->state->get("absolute_position");

  playerAbsolutePos->horz += playerTraj->position.horz;
  playerAbsolutePos->vert += playerTraj->position.vert;
  playerAbsolutePos->depth += playerTraj->position.depth;

  playerAngle->pitch += playerTraj->angle.pitch;
  playerAngle->roll += playerTraj->angle.roll;
  playerAngle->yaw += playerTraj->angle.yaw;

  playerTraj->position.horz *= (playerTraj->positionRate.horz);
  playerTraj->position.vert *= (playerTraj->positionRate.vert);
  playerTraj->position.depth *= (playerTraj->positionRate.depth);

  playerTraj->angle.pitch *= (playerTraj->angleRate.pitch);
  playerTraj->angle.roll *= (playerTraj->angleRate.roll);
  playerTraj->angle.yaw *= (playerTraj->angleRate.yaw);

  if (playerAbsolutePos->horz < 0) {
    playerAbsolutePos->horz = 0;
    playerTraj->position.horz = 0;
  }

  if (playerAbsolutePos->vert < 0) {
    playerAbsolutePos->vert = 0;
    playerTraj->position.vert = 0;
  }

  if (playerAbsolutePos->horz > (background->width - player->width)) {
    playerAbsolutePos->horz = background->width - player->width;
    playerTraj->position.horz = 0;
  }

  if (playerAbsolutePos->vert > background->height) {
    playerAbsolutePos->vert = background->height;
    playerTraj->position.vert = 0;
  }

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

    playerTraj->position.horz += 3 * playerHorzRatio;
    playerTraj->position.vert += 3 * playerVertRatio;
  }

  if (KeyboardInput::isPressed(44) && (SDL_GetTicks() - lastBulletTimestamp) > BULLET_DELAY) {
    // fire a pellet
    Bullet* bullet = new Bullet();

    bullet->onEvaluate(bulletEvaluateCallback, (void*)sceneElements);

    bullet->state->set("absolute_position", new Position(
      (background->width / 2) - (backgroundView->size.horz / 2) - (player->width / 2) + 20,
      (background->height / 2) - (backgroundView->size.vert / 2) - (player->width / 2) + 20
    ));

    Position* bulletAbsolutePos = (Position*)bullet->state->get("absolute_position");
    Position* bulletPos = (Position*)bullet->state->get("position");
    Angle* bulletAngle = (Angle*)bullet->state->get("angle");
    Trajectory* bulletTraj = (Trajectory*)bullet->state->get("trajectory");

    bulletAngle->center.horz = playerAngle->center.horz - 20;
    bulletAngle->center.vert = playerAngle->center.vert - 20;

    bulletHorzRatio = playerHorzRatio;
    bulletVertRatio = playerVertRatio;

    bulletTraj->position.horz = 36 * bulletHorzRatio;
    bulletTraj->position.vert = 36 * bulletVertRatio;

    bulletAbsolutePos->horz = playerAbsolutePos->horz + 20;
    bulletAbsolutePos->vert = playerAbsolutePos->vert + 20;

    bulletAngle->pitch = playerAngle->pitch + 132;

    lastBulletTimestamp = SDL_GetTicks();

    char* bulletIdentifier;

    sprintf(bulletIdentifier, "%lu", bullet->getIdentifier());

    bullets->set(bulletIdentifier, bullet);
  }

  // keep angle within 360 degrees
  // TODO: enforce this from a state callback.
  playerAngle->pitch = playerAngle->pitch < 0 ? 360 - abs(playerAngle->pitch) : playerAngle->pitch;
  playerAngle->pitch = playerAngle->pitch >= 360 ? playerAngle->pitch / 360 : playerAngle->pitch;

  return (void*)NULL;
}


int main(int argc, char *argv[]) {
  Window* win = new Window();
  Application* app = new Application();

  PlayerOne* player = new PlayerOne();
  Background* background = new Background();

  sceneElements->set("player", player);
  sceneElements->set("background", background);

  app->on("KEYBOARD", keyboardCallback, (void*)player);
  app->on("QUIT", quitCallback, (void*)NULL);
  win->on("CLOSED", closedCallback, (void*)NULL);

  player->onEvaluate(playerEvaluateCallback, (void*)sceneElements);
  background->onEvaluate(backgroundEvaluateCallback, (void*)sceneElements);

  Position* playerPos = (Position*)player->state->get("position");
  Angle* playerAngle = (Angle*)player->state->get("angle");
  View* backgroundView = (View*)background->state->get("view");

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

  Position* playerAbsolutePos = (Position*)player->state->get("absolute_position");

  backgroundView->position.horz = playerAbsolutePos->horz - round(backgroundView->size.horz / 2);
  backgroundView->position.vert = playerAbsolutePos->vert - round(backgroundView->size.vert / 2);


  win->open("blasteroids", 600, 150, SCREEN_WIDTH, SCREEN_HEIGHT);

  SDL_Renderer* renderer = win->getRenderer();

  app->start();

  KeyboardInput::updateState();

  unsigned long int frameElapsed = 0;
  unsigned long int frameDelay = 1000 / FRAMERATE;

  unsigned long int frameStart = 0;
  unsigned long int framePasses = 0;
  unsigned long int frameEvalDelay = 100;

  while (app->isActive) {

    if (frameElapsed == 0 || frameElapsed > frameDelay) {
      frameStart = SDL_GetTicks();

      Event::evaluate();

      background->evaluate();
      player->evaluate();

      background->render(renderer);
      player->render(renderer);

      List<Bullet*>* bulletsVals = bullets->getValues();

      unsigned long int bulletsValsLen = bulletsVals->getLength();

      for (unsigned long int bulletsValsIdx = 0; bulletsValsIdx < bulletsValsLen; bulletsValsIdx++) {
        Bullet* bullet = bulletsVals->get(bulletsValsIdx);

        bullet->evaluate();
        bullet->render(renderer);
      }

      //win->clear();

      win->render();

      frameElapsed += SDL_GetTicks() - frameStart;
      framePasses++;

      if (framePasses % frameEvalDelay == 0) {
        float avgFrameTime = (float)frameElapsed / (float)framePasses;

        printf("\n[%u] AVG FRAME TIME: %.2fms", SDL_GetTicks(), avgFrameTime);

        frameElapsed = 0;
        framePasses = 0;
      }

    }

  }

  delete background;
  delete player;

  delete win;
  delete app;
}
