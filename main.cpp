
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
#include "./src/lib/background.hpp"
//#include "./lib/scene/background.hpp"


const unsigned char FRAMERATE = 120; // fps
const unsigned int SCREEN_WIDTH = 1024;
const unsigned int SCREEN_HEIGHT = 769;

Window* win = new Window();
Application* app = new Application();

PlayerOne* player = new PlayerOne();
Background* background = new Background();


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

  Position* playerPos = (Position*)player->state->get("position");
  Angle* playerAngle = (Angle*)player->state->get("angle");
  Trajectory* playerTraj = (Trajectory*)player->state->get("trajectory");
  Trajectory* backgroundTraj = (Trajectory*)background->state->get("trajectory");
  View* backgroundView = (View*)background->state->get("view");

  if (playerAngle->pitch >= 180) {
    horzRatio = -(((270 - playerAngle->pitch) / 90));
  } else {
    horzRatio = ((90 - playerAngle->pitch) / 90);
  }

  if (playerAngle->pitch <= 90) {
    vertRatio = (playerAngle->pitch) / 90;
  } else if (playerAngle->pitch > 270) {
    vertRatio = -(360 - playerAngle->pitch) / 90;
  } else {
    vertRatio = (180 - playerAngle->pitch) / 90;
  }

  if (KeyboardInput::isReleased(82)) {
    printf("stopping\n");
    player->setAction("standing_still");
  }

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

    if (backgroundView->position.horz <= 0) {
      // move our player sprite horizontally along our left borders.
      playerTraj->position.horz += 4 * horzRatio;
      backgroundView->position.horz = 0;

    } else {
      // move our background horizontally around our player.
      backgroundTraj->position.horz += 4 * horzRatio;
    }

    if (backgroundView->position.vert <= 0) {
      // move our player sprite verticall along our left borders.
      playerTraj->position.vert += 4 * vertRatio;
      backgroundView->position.vert = 0;

    } else {
      // move our background vertically around our player.
      backgroundTraj->position.vert += 4 * vertRatio;
    }

  }

  unsigned long int horzBorder = round((backgroundView->size.horz / 2) - (player->width / 2));
  unsigned long int vertBorder = round((backgroundView->size.vert / 2) - (player->height / 2));

  if (backgroundView->position.horz <= 0
    && playerPos->horz >= horzBorder
    && playerTraj->position.horz > 0
  ) {
    backgroundTraj->position.horz = playerTraj->position.horz;
    playerPos->horz = horzBorder;
    playerTraj->position.horz = 0;
  } else if (backgroundView->position.horz <= 0 && backgroundTraj->position.horz < 0) {
    playerTraj->position.horz = backgroundTraj->position.horz;
    backgroundView->position.horz = 0;
    backgroundTraj->position.horz = 0;
  }

  if (backgroundView->position.vert <= 0
    && playerPos->vert >= vertBorder
    && playerTraj->position.vert > 0
  ) {
    backgroundTraj->position.vert = playerTraj->position.vert;
    playerPos->vert = vertBorder;
    playerTraj->position.vert = 0;
  } else if (backgroundView->position.vert <= 0 && backgroundTraj->position.vert < 0) {
    playerTraj->position.vert = backgroundTraj->position.vert;
    backgroundView->position.vert = 0;
    backgroundTraj->position.vert = 0;
  }










  //printf("\n===========================\n");
  //printf("CLOCK: %d\n", SDL_GetTicks());
  //printf("\n");
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
  //printf("BACKGROUND HORZ SIZE: %f\n", background->width);
  //printf("BACKGROUND VERT SIZE: %f\n", background->height);
  //printf("===========================\n\n");




  if (playerPos->horz < 0) {
    playerPos->horz = 0;
  }

  if (playerPos->vert < 0) {
    playerPos->vert = 0;
  }

  if (backgroundView->position.horz >= background->width - backgroundView->size.horz) {
    backgroundView->position.horz = background->width - backgroundView->size.horz;
  }

  if (backgroundView->position.vert >= background->height - backgroundView->size.vert) {
    backgroundView->position.vert = background->height - backgroundView->size.vert;
  }











  // keep angle within 360 degrees
  // TODO: enforce this from a state callback.
  playerAngle->pitch = playerAngle->pitch < 0 ? 360 - abs(playerAngle->pitch) : playerAngle->pitch;
  playerAngle->pitch = playerAngle->pitch >= 360 ? playerAngle->pitch / 360 : playerAngle->pitch;

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
  //Image* backgroundImage = Image::load("./background2.bmp", 0, 0, 3840, 1264);

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


  Position* playerPos = (Position*)player->state->get("position");
  Angle* playerAngle = (Angle*)player->state->get("angle");
  View* backgroundView = (View*)background->state->get("view");

  playerPos->horz = round((SCREEN_WIDTH / 2) - (player->width / 2));
  playerPos->vert = round((SCREEN_HEIGHT / 2) - (player->height / 2));

  playerAngle->center.horz = 43;
  playerAngle->center.vert = 43;

  backgroundView->size.horz = SCREEN_WIDTH;
  backgroundView->size.vert = SCREEN_HEIGHT;
  backgroundView->position.horz = round((background->width / 2) - (SCREEN_WIDTH / 2));
  backgroundView->position.vert = round((background->height / 2) - (SCREEN_HEIGHT / 2));

  app->start();

  float start = 0.0;
  float elapsed = 0.0;

  unsigned long int totalElapsed = 0;
  unsigned long int numPasses = 0;

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

    totalElapsed += elapsed;
    numPasses++;

    if (numPasses % 5000 == 0) {
      printf("\n[%u] AVG FRAME TIME: %ldms", SDL_GetTicks(), (totalElapsed / numPasses));
    }

  }

  //SDL_Delay(5000);

  delete app;
  delete win;

  SDL_Quit();
}
