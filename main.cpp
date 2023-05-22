
#if __cplusplus < 201703L
  #error expects C++17 standard.
#endif


#include <string.h>
#include <math.h>
#include <time.h>

#include "./src/lib/bullet.hpp"
#include "./src/lib/background.hpp"
#include "./src/lib/player.hpp"

#include "./lib/core/keyboard.hpp"

#include "./lib/runtime/window.hpp"
#include "./lib/runtime/application.hpp"

#include "./lib/runtime/data/view.hpp"
#include "./lib/runtime/data/angle.hpp"
#include "./lib/runtime/data/position.hpp"

#include "./lib/scene.hpp"

const unsigned long int SCREEN_WIDTH = 1024;
const unsigned long int SCREEN_HEIGHT = 769;

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
  KeyboardEventParams* parsedInp = reinterpret_cast<KeyboardEventParams*>(inp);
  Player* player = reinterpret_cast<Player*>(data);

  //const unsigned char* keyboardState = SDL_GetKeyboardState(NULL);
  KeyboardInput::updateState();

  return (void*)NULL;
}

//void* windowPresentCallback(void* inp, void* data) {
//  UserEventParams* parsedInp = reinterpret_cast<UserEventParams*>(inp);
//  Window* win = reinterpret_cast<Window*>(data);
//
//  SDL_RenderPresent(win->getRenderer());
//  //printf("\n[%u] RENDERING!!!!", SDL_GetTicks());
//
//  return (void*)NULL;
//}

void* sceneEvaluateCallback(void* inp, void* data) {
  Scene* scene = reinterpret_cast<Scene*>(inp);

  Background* background = (Background*)scene->getElement("background");
  View* backgroundView = (View*)background->state->get("view");

  backgroundView->position.horz = scene->view->position.horz;
  backgroundView->position.vert = scene->view->position.vert;


  return (void*)NULL;
}

void* backgroundEvaluateCallback(void* inp, void* data) {
  Background* background = reinterpret_cast<Background*>(inp);
  Scene* scene = reinterpret_cast<Scene*>(data);

  Player* player = (Player*)scene->getElement("player");

  Trajectory* backgroundTraj = (Trajectory*)background->state->get("trajectory");

  Position* backgroundAbsolutePos = (Position*)scene->state->get("absolute_position");
  Position* backgroundPos = (Position*)scene->state->get("position");

  scene->view->position.horz += backgroundTraj->position.horz;
  scene->view->position.vert += backgroundTraj->position.vert;
  scene->view->position.depth += backgroundTraj->position.depth;

  backgroundTraj->position.horz *= backgroundTraj->positionRate.horz;
  backgroundTraj->position.vert *= backgroundTraj->positionRate.vert;
  backgroundTraj->position.depth *= backgroundTraj->positionRate.depth;

  return (void*)NULL;
}

void* bulletEvaluateCallback(void* inp, void* data) {
  Bullet* bullet = reinterpret_cast<Bullet*>(inp);
  Scene* scene = reinterpret_cast<Scene*>(data);

  Player* player = (Player*)scene->getElement("player");
  Background* background = (Background*)scene->getElement("background");

  Position* playerPos = (Position*)player->state->get("position");
  Angle* playerAngle = (Angle*)player->state->get("angle");
  Trajectory* playerTraj = (Trajectory*)player->state->get("trajectory");

  Position* playerAbsolutePos = (Position*)player->state->get("absolute_position");
  Position* bulletAbsolutePos = (Position*)bullet->state->get("absolute_position");

  Position* bulletPos = (Position*)bullet->state->get("position");
  Angle* bulletAngle = (Angle*)bullet->state->get("angle");
  Trajectory* bulletTraj = (Trajectory*)bullet->state->get("trajectory");

  bulletAbsolutePos->horz += bulletTraj->position.horz;
  bulletAbsolutePos->vert += bulletTraj->position.vert;
  bulletAbsolutePos->depth += bulletTraj->position.depth;

  if (bulletAbsolutePos->horz > scene->view->position.horz
    && bulletAbsolutePos->horz < (scene->view->position.horz + scene->view->size.horz)
    && bulletAbsolutePos->vert > scene->view->position.vert
    && bulletAbsolutePos->vert < (scene->view->position.vert + scene->view->size.vert)
  ) {
    // our bullet is visible within our screen.
    bulletPos->horz = (bulletAbsolutePos->horz - scene->view->position.horz);
    bulletPos->vert = (bulletAbsolutePos->vert - scene->view->position.vert);

  }

  if (bulletAbsolutePos->horz < 0
    || bulletAbsolutePos->vert < 0
    || bulletAbsolutePos->horz > scene->size->horz
    || bulletAbsolutePos->vert > scene->size->vert
  ) {
    // our bullet has left our space.

    bullet->isActive = false;
  }

  return (void*)NULL;
}

void* playerEvaluateCallback(void* inp, void* data) {
  Player* player = reinterpret_cast<Player*>(inp);
  Scene* scene = reinterpret_cast<Scene*>(data);

  Background* background = (Background*)scene->getElement("background");

  Position* playerPos = (Position*)player->state->get("position");
  Angle* playerAngle = (Angle*)player->state->get("angle");
  Scale* playerScale = (Scale*)player->state->get("scale");
  Trajectory* playerTraj = (Trajectory*)player->state->get("trajectory");
  Trajectory* backgroundTraj = (Trajectory*)background->state->get("trajectory");

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

  if (playerAbsolutePos->horz < round(player->width / 2)) {
    playerAbsolutePos->horz = round(player->height / 2);
    playerTraj->position.horz = 0;
  }

  if (playerAbsolutePos->vert < round(player->height / 2)) {
    playerAbsolutePos->vert = round(player->height / 2);
    playerTraj->position.vert = 0;
  }

  if (playerAbsolutePos->horz > (scene->size->horz - round(player->width / 2))) {
    playerAbsolutePos->horz = scene->size->horz - round(player->width / 2);
    playerTraj->position.horz = 0;
  }

  if (playerAbsolutePos->vert > (scene->size->vert - round(player->height / 2))) {
    playerAbsolutePos->vert = scene->size->vert - round(player->height / 2);
    playerTraj->position.vert = 0;
  }

  if (playerAbsolutePos->horz > round(scene->view->size.horz / 2)
    && playerAbsolutePos->horz < scene->size->horz - round(scene->view->size.horz / 2)
  ) {
    playerPos->horz = round(scene->view->size.horz / 2);
    scene->view->position.horz = playerAbsolutePos->horz - round(scene->view->size.horz / 2);

  } else if (playerAbsolutePos->horz < round(scene->view->size.horz / 2)) {
    playerPos->horz = playerAbsolutePos->horz;

  } else if (playerAbsolutePos->horz > scene->size->horz - round(scene->view->size.horz / 2)) {
    playerPos->horz = scene->view->size.horz - (scene->size->horz - playerAbsolutePos->horz);
  }


  if (playerAbsolutePos->vert > round(scene->view->size.vert / 2)
    && playerAbsolutePos->vert < scene->size->vert - round(scene->view->size.vert / 2)
  ) {
    playerPos->vert = round(scene->view->size.vert / 2);
    scene->view->position.vert = playerAbsolutePos->vert - round(scene->view->size.vert / 2);

  } else if (playerAbsolutePos->vert < round(scene->view->size.vert / 2)) {
    playerPos->vert = playerAbsolutePos->vert;

  } else if (playerAbsolutePos->vert > scene->size->vert - round(scene->view->size.vert / 2)) {
    playerPos->vert = scene->view->size.vert - (scene->size->vert - playerAbsolutePos->vert);
  }


  float playerHorzRatio = 0.0;
  float playerVertRatio = 0.0;

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
    playerTraj->angle.pitch -= 1;
  }

  if (KeyboardInput::isPressed(79)) {
    // turn right.
    player->setAction("turning_right");
    playerTraj->angle.pitch += 1;
  }

  if (KeyboardInput::isPressed(82)) {
    // move forward.
    player->setAction("moving_forward");

    playerTraj->position.horz += 2 * playerHorzRatio;
    playerTraj->position.vert += 2 * playerVertRatio;
  }

  if (KeyboardInput::isPressed(44)
    && (SDL_GetTicks() - lastBulletTimestamp) > Bullet::DELAY
  ) {
    // fire a pellet

    for (unsigned long int bulletIdx = 0; bulletIdx < scene->getNumElements(); bulletIdx++) {
      char* name = new char();

      sprintf(name, "bullet-%.2lu", bulletIdx);

      SceneElement* element = (SceneElement*)scene->getElement(name);

      if (element == NULL) {
        continue;
      }

      int typeCmpRes = strcmp(element->getType(), "bullet");

      if (element->isActive == false && typeCmpRes == 0) {
        Bullet* bullet = reinterpret_cast<Bullet*>(element);

        bullet->state->set("absolute_position", new Position(
          (scene->size->horz / 2) - (scene->view->size.horz / 2) - (player->width / 2) + 20,
          (scene->size->vert / 2) - (scene->view->size.vert / 2) - (player->width / 2) + 20
        ));

        Position* bulletAbsolutePos = (Position*)bullet->state->get("absolute_position");
        Position* bulletPos = (Position*)bullet->state->get("position");
        Angle* bulletAngle = (Angle*)bullet->state->get("angle");
        Trajectory* bulletTraj = (Trajectory*)bullet->state->get("trajectory");

        bulletAngle->center.horz = playerAngle->center.horz - 20;
        bulletAngle->center.vert = playerAngle->center.vert - 20;

        bulletTraj->position.horz = 24 * playerHorzRatio;
        bulletTraj->position.vert = 24 * playerVertRatio;

        bulletAbsolutePos->horz = playerAbsolutePos->horz;
        bulletAbsolutePos->vert = playerAbsolutePos->vert;

        bulletAngle->pitch = playerAngle->pitch + 132;

        bullet->isActive = true;

        lastBulletTimestamp = SDL_GetTicks();

        break;
      }

    }

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
  Scene* scene = new Scene();

  Player* player = Player::loadAssets(scene, playerEvaluateCallback);
  Background* background = Background::loadAssets(scene, backgroundEvaluateCallback);

  scene->size->horz = 3000;
  scene->size->vert = 1688;

  scene->addElement("background", background);
  scene->addElement("player", player);

  for (unsigned long int bulletsIdx = 0; bulletsIdx < Bullet::MAX_COUNT; bulletsIdx++) {
    Bullet* bullet = Bullet::loadAssets(scene, bulletEvaluateCallback);

    char* name = new char();

    sprintf(name, "bullet-%.2lu", bulletsIdx);

    scene->addElement(name, bullet);
  }

  scene->onEvaluate(sceneEvaluateCallback, (void*)NULL);

  app->on("KEYBOARD", keyboardCallback, (void*)player);
  app->on("QUIT", quitCallback, (void*)NULL);
  win->on("CLOSED", closedCallback, (void*)NULL);
  //win->on("PRESENT", windowPresentCallback, (void*)win);

  Position* playerPos = (Position*)player->state->get("position");
  Angle* playerAngle = (Angle*)player->state->get("angle");
  View* backgroundView = (View*)background->state->get("view");

  playerAngle->center.horz = 43;
  playerAngle->center.vert = 43;

  // TODO: we shouldn't have to update both backgroundView and scene from here.
  backgroundView->size.horz = SCREEN_WIDTH;
  backgroundView->size.vert = SCREEN_HEIGHT;
  scene->view->size.horz = SCREEN_WIDTH;
  scene->view->size.vert = SCREEN_HEIGHT;

  scene->view->position.horz = round((scene->size->horz / 2) - (scene->view->size.horz / 2));
  scene->view->position.vert = round((scene->size->vert / 2) - (scene->view->size.vert / 2));

  player->state->set("absolute_position", new Position(
    (scene->size->horz / 2) - (scene->view->size.horz / 2) - (player->width / 2),
    (scene->size->vert / 2) - (scene->view->size.vert / 2) - (player->width / 2)
  ));

  background->state->set("absolute_position", new Position());

  Position* playerAbsolutePos = (Position*)player->state->get("absolute_position");

  scene->view->position.horz = playerAbsolutePos->horz - round(scene->view->size.horz / 2);
  scene->view->position.vert = playerAbsolutePos->vert - round(scene->view->size.vert / 2);

  win->open("blasteroids", 600, 150, SCREEN_WIDTH, SCREEN_HEIGHT);

  SDL_Renderer* renderer = win->getRenderer();

  app->start();

  KeyboardInput::updateState();

  unsigned long int frameElapsed = 0;

  unsigned long int frameStart = 0;
  unsigned long int framePasses = 0;
  unsigned long int frameEvalDelay = 100;

  while (app->isActive) {

    Event::evaluate();

    frameStart = SDL_GetTicks();

    //win->clear();

    scene->evaluate();
    scene->render(renderer);


    frameElapsed += SDL_GetTicks() - frameStart;
    framePasses++;

    win->render();

    if (framePasses % frameEvalDelay == 0) {
      float avgFrameTime = (float)frameElapsed / (float)framePasses;

      printf("\n[%u] AVG FRAME TIME: %.2fms", SDL_GetTicks(), avgFrameTime);

      frameElapsed = 0;
      framePasses = 0;
    }

  }

  delete scene;

  delete win;
  delete app;
}
