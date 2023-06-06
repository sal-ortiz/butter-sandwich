
#ifndef _GAME_PLAYER_HPP

  #define _GAME_PLAYER_HPP

  #include <string.h>

  #include "../../lib/core/keyboard.hpp"
  #include "../../lib/core/image.hpp"
  #include "../../lib/runtime/sprite.hpp"
  #include "../../lib/runtime/data/trajectory.hpp"
  #include "../../lib/runtime/data/position.hpp"
  #include "../../lib/runtime/data/angle.hpp"
  #include "../../lib/runtime/data/scale.hpp"
  #include "../../lib/runtime/data/view.hpp"
  #include "../../lib/scene.hpp"


  unsigned long int lastBulletTimestamp = 0;

  class Player: public SceneCharacter {

    public:

      Player() {
        Trajectory* traj = (Trajectory*)this->state->get("trajectory");

        traj->positionRate.horz = 0.925;
        traj->positionRate.vert = 0.925;
        traj->positionRate.depth = 0.925;

        traj->angleRate.pitch = 0.85;
        traj->angleRate.roll = 0.85;
        traj->angleRate.yaw = 0.85;

        traj->scaleRate.horz = 0.90;
        traj->scaleRate.vert = 0.90;
        traj->scaleRate.depth = 0.90;

        this->isActive = true;
      }

      static Player* loadAssets(Scene* scene) {
        Player* player = new Player();

        Sprite* standingStillSprite = new Sprite();
        Sprite* movingForwardSprite = new Sprite();
        Sprite* turningLeftSprite = new Sprite();
        Sprite* turningRightSprite = new Sprite();

        Image* shipStandingStill = Image::load("./ship_sheet.png", 390, 150, 75, 75);
        Image* shipTurningLeft = Image::load("./ship_sheet.png", 490, 50, 75, 75);
        Image* shipTurningRight = Image::load("./ship_sheet.png", 190, 50, 75, 75);
        Image* shipMovingForward = Image::load("./ship_sheet.png", 90, 50, 75, 75);

        standingStillSprite->addFrame(shipStandingStill, 0);
        movingForwardSprite->addFrame(shipMovingForward, 0);
        turningLeftSprite->addFrame(shipTurningLeft, 0);
        turningRightSprite->addFrame(shipTurningRight, 0);

        standingStillSprite->setLoop(false);
        movingForwardSprite->setLoop(false);
        turningLeftSprite->setLoop(false);
        turningRightSprite->setLoop(false);

        player->addSprite("standing_still", standingStillSprite);
        player->addSprite("moving_forward", movingForwardSprite);
        player->addSprite("turning_left", turningLeftSprite);
        player->addSprite("turning_right", turningRightSprite);

        player->setAction("standing_still");

        Scale* playerScale = (Scale*)player->state->get("scale");

        playerScale->horz = 1.0;
        playerScale->vert = 1.0;

        player->onEvaluate(Player::evaluateCallback, scene);

        return player;
      }

      static void* evaluateCallback(void* inp, void* data) {
        Player* player = reinterpret_cast<Player*>(inp);
        Scene* scene = reinterpret_cast<Scene*>(data);

        Background* background = (Background*)scene->getElement("background");

        Position* playerPos = (Position*)player->state->get("position");
        Angle* playerAngle = (Angle*)player->state->get("angle");
        Trajectory* playerTraj = (Trajectory*)player->state->get("trajectory");

        Position* playerAbsolutePos = (Position*)player->state->get("absolute_position");
        Position* backgroundAbsolutePos = (Position*)background->state->get("absolute_position");

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
          // enforce our leftmost border
          playerAbsolutePos->horz = round(player->width / 2);
          playerTraj->position.horz = 0;
        }

        if (playerAbsolutePos->vert < round(player->height / 2)) {
          // enforce our upper border
          playerAbsolutePos->vert = round(player->height / 2);
          playerTraj->position.vert = 0;
        }

        if (playerAbsolutePos->horz > (scene->size->horz - round(player->width / 2))) {
          // enforce our rightmost border
          playerAbsolutePos->horz = scene->size->horz - round(player->width / 2);
          playerTraj->position.horz = 0;
        }

        if (playerAbsolutePos->vert > (scene->size->vert - round(player->height / 2))) {
          // enforce our lower border
          playerAbsolutePos->vert = scene->size->vert - round(player->height / 2);
          playerTraj->position.vert = 0;
        }

        if (playerAbsolutePos->horz > round(scene->view->size.horz / 2)
          && playerAbsolutePos->horz < scene->size->horz - round(scene->view->size.horz / 2)
        ) {
          // moving horizontally around the center of our map
          playerPos->horz = round(scene->view->size.horz / 2);
          scene->view->position.horz = playerAbsolutePos->horz - round(scene->view->size.horz / 2);

        } else if (playerAbsolutePos->horz < round(scene->view->size.horz / 2)) {
          // moving horizontally around the left border of our map
          playerPos->horz = playerAbsolutePos->horz;

        } else if (playerAbsolutePos->horz > scene->size->horz - round(scene->view->size.horz / 2)) {
          // moving horizontally around the right border of our map
          playerPos->horz = scene->view->size.horz - (scene->size->horz - playerAbsolutePos->horz);
        }

        if (playerAbsolutePos->vert > round(scene->view->size.vert / 2)
          && playerAbsolutePos->vert < scene->size->vert - round(scene->view->size.vert / 2)
        ) {
          // moving vertically around the center of our map.
          playerPos->vert = round(scene->view->size.vert / 2);
          scene->view->position.vert = playerAbsolutePos->vert - round(scene->view->size.vert / 2);

        } else if (playerAbsolutePos->vert < round(scene->view->size.vert / 2)) {
          // moving vertically around the upper border of our map.
          playerPos->vert = playerAbsolutePos->vert;

        } else if (playerAbsolutePos->vert > scene->size->vert - round(scene->view->size.vert / 2)) {
          // moving vertically around the lower border of our map.
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

          playerTraj->position.horz += 1.5 * playerHorzRatio;
          playerTraj->position.vert += 1.5 * playerVertRatio;
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

              bulletAngle->center.horz = playerAngle->center.horz - 36;
              bulletAngle->center.vert = playerAngle->center.vert - 36;

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

  };

#endif
