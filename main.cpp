
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
//#include "./lib/scene/background.hpp"


const unsigned long int FRAMERATE = 120; // fps
const unsigned long int SCREEN_WIDTH = 1024;
const unsigned long int SCREEN_HEIGHT = 769;

float horzRatio = 1.0;
float vertRatio = 0.0;

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

void* keyboardCallback(void* inp, void* data) {
  //PlayerOne* player = reinterpret_cast<PlayerOne*>(data);
  const unsigned char* keyboardState = SDL_GetKeyboardState(NULL);

  Trajectory* playerTraj = (Trajectory*)player->state->get("trajectory");
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
  if (keyboardState[82]) {
    //// move forward.
    //player->setAction("moving_forward");
    //playerTraj->position.horz += 1 * horzRatio;
    //playerTraj->position.vert += 1 * vertRatio;
  }
//
//  //// keep angle within 360 degrees
//  //player->angle->pitch = player->angle->pitch < 0 ? 360 - abs(player->angle->pitch) : player->angle->pitch;
//  //player->angle->pitch = player->angle->pitch >= 360 ? player->angle->pitch / 360 : player->angle->pitch;
//

  return (void*)NULL;
}

void* evaluateCallback(void* inp, void* data) {
  PlayerOne* player = reinterpret_cast<PlayerOne*>(inp);
  SceneBackground* background = reinterpret_cast<SceneBackground*>(data);

  Position* playerPos = (Position*)player->state->get("position");
  Angle* playerAngle = (Angle*)player->state->get("angle");
  Trajectory* playerTraj = (Trajectory*)player->state->get("trajectory");
  Trajectory* backgroundTraj = (Trajectory*)background->state->get("trajectory");
  View* backgroundView = (View*)background->state->get("view");

  Position* playerAbsolutePos = (Position*)player->state->get("absolute_position");

  unsigned long int horzLowerLimit = round(backgroundView->size.horz / 2);
  unsigned long int horzUpperLimit = background->width - round(backgroundView->size.horz / 2);

  unsigned long int vertLowerLimit = round(backgroundView->size.vert / 2);
  unsigned long int vertUpperLimit = background->height - round(backgroundView->size.vert / 2);


  if (playerAbsolutePos->horz <= (horzLowerLimit - (player->width / 2))) {
    // handle the left horizontal edge of our background.
    playerPos->horz = playerAbsolutePos->horz;

  } else if (playerAbsolutePos->horz > (horzUpperLimit - (backgroundView->size.horz / 2)) - (player->width / 2)) {
    // handle the right horizontal edge of our background.
    playerPos->horz = ((background->width - horzUpperLimit) - (horzUpperLimit - playerAbsolutePos->horz)) + (backgroundView->size.horz / 2);

  } else {
    backgroundView->position.horz = playerAbsolutePos->horz;

    playerPos->horz = (backgroundView->size.horz / 2) - (player->width / 2);

  }


  if (playerAbsolutePos->vert < (vertLowerLimit - (player->height / 2))) {
    playerPos->vert = playerAbsolutePos->vert;
  } else if (playerAbsolutePos->vert > (vertUpperLimit - (backgroundView->size.vert / 2)) - (player->height / 2)) {
    playerPos->vert = ((background->height - vertUpperLimit) - (vertUpperLimit - playerAbsolutePos->vert)) + (backgroundView->size.vert / 2);

  } else {
    backgroundView->position.vert = playerAbsolutePos->vert;

    playerPos->vert = (backgroundView->size.vert / 2) - (player->height / 2);
  }

  if (playerAbsolutePos->horz < 0) {
    // enforce our lower horizontal limit.
    playerAbsolutePos->horz = 0;
    playerTraj->position.horz = 0;
  }

  if (playerAbsolutePos->vert < 0) {
    // enforce our lower vertical limit.
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

    playerTraj->position.horz += 4 * horzRatio;
    playerTraj->position.vert += 4 * vertRatio;
  }


  // keep angle within 360 degrees
  // TODO: enforce this from a state callback.
  playerAngle->pitch = playerAngle->pitch < 0 ? 360 - abs(playerAngle->pitch) : playerAngle->pitch;
  playerAngle->pitch = playerAngle->pitch >= 360 ? playerAngle->pitch / 360 : playerAngle->pitch;

  return (void*)NULL;
}


int main(int argc, char *argv[]) {
  app->on("KEYBOARD", keyboardCallback, (void*)player);
  app->on("QUIT", quitCallback, (void*)NULL);
  win->on("CLOSED", closedCallback, (void*)NULL);

  player->onEvaluate(evaluateCallback, (void*)background);

  Sprite* standingStillSprite = new Sprite();
  Sprite* movingForwardSprite = new Sprite();
  Sprite* turningLeftSprite = new Sprite();
  Sprite* turningRightSprite = new Sprite();
  Sprite* backgroundSprite = new Sprite();


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

  playerAngle->center.horz = 43;
  playerAngle->center.vert = 43;

  backgroundView->size.horz = SCREEN_WIDTH;
  backgroundView->size.vert = SCREEN_HEIGHT;
  backgroundView->position.horz = round((background->width / 2) - (SCREEN_WIDTH / 2));
  backgroundView->position.vert = round((background->height / 2) - (SCREEN_HEIGHT / 2));

  player->state->set("absolute_position", new Position(
    (background->width / 2) - (backgroundView->size.horz / 2),
    (background->height / 2) - (backgroundView->size.vert / 2)
  ));

  win->open("The window!", 150, 150, SCREEN_WIDTH, SCREEN_HEIGHT);

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

      Event::evaluate();
      KeyboardInput::updateState();

      background->evaluate();
      background->render(renderer);

      player->evaluate();
      player->render(renderer);

      win->render();

      frameElapsed += SDL_GetTicks() - frameStart;
      framePasses++;

      if (framePasses % frameEvalDelay == 0) {
        float avgFrameTime = frameElapsed / framePasses;

        printf("\n[%u] AVG FRAME TIME: %f per %lu frames", SDL_GetTicks(), avgFrameTime, frameEvalDelay);

        frameElapsed = 0;
        framePasses = 0;
      }


    }

  }

  delete win;
  delete app;
}
