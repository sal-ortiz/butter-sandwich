
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
        Trajectory* trajectory = (Trajectory*)this->state->get("trajectory");

        trajectory->positionRate.horz = 0.925;
        trajectory->positionRate.vert = 0.925;
        trajectory->positionRate.depth = 0.925;

        trajectory->angleRate.pitch = 0.85;
        trajectory->angleRate.roll = 0.85;
        trajectory->angleRate.yaw = 0.85;

        trajectory->scaleRate.horz = 0.90;
        trajectory->scaleRate.vert = 0.90;
        trajectory->scaleRate.depth = 0.90;

        this->isActive = true;
      }

      static Player* loadAssets(Scene* scene) {
        Player* player = new Player();

        Sprite* standingStillSprite = new Sprite();
        Sprite* movingForwardSprite = new Sprite();
        Sprite* turningLeftSprite = new Sprite();
        Sprite* turningRightSprite = new Sprite();

        Image* shipStandingStill = Image::load("./src/assets/ship_sheet.png", 390, 150, 75, 75);
        Image* shipTurningLeft = Image::load("./src/assets/ship_sheet.png", 490, 50, 75, 75);
        Image* shipTurningRight = Image::load("./src/assets/ship_sheet.png", 190, 50, 75, 75);
        Image* shipMovingForward = Image::load("./src/assets/ship_sheet.png", 90, 50, 75, 75);

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

        Scale* scale = (Scale*)player->state->get("scale");
        Angle* angle = (Angle*)player->state->get("angle");
        Position* absPosition = (Position*)player->state->get("absolute_position");

        scale->horz = 1.0;
        scale->vert = 1.0;

        angle->center.horz = 43;
        angle->center.vert = 43;

        absPosition->horz = scene->size->horz / 2;
        absPosition->vert = scene->size->vert / 2;

        player->onEvaluate(Player::evaluateCallback, scene);

        return player;
      }

      static void* evaluateCallback(void* inp, void* dataOne, void* dataTwo) {
        Player* player = reinterpret_cast<Player*>(inp);
        Scene* scene = reinterpret_cast<Scene*>(dataOne);

        Position* position = (Position*)player->state->get("position");
        Angle* angle = (Angle*)player->state->get("angle");
        Trajectory* trajectory = (Trajectory*)player->state->get("trajectory");

        Position* absPosition = (Position*)player->state->get("absolute_position");

        absPosition->horz += trajectory->position.horz;
        absPosition->vert += trajectory->position.vert;
        absPosition->depth += trajectory->position.depth;

        angle->pitch += trajectory->angle.pitch;
        angle->roll += trajectory->angle.roll;
        angle->yaw += trajectory->angle.yaw;

        trajectory->position.horz *= (trajectory->positionRate.horz);
        trajectory->position.vert *= (trajectory->positionRate.vert);
        trajectory->position.depth *= (trajectory->positionRate.depth);

        trajectory->angle.pitch *= (trajectory->angleRate.pitch);
        trajectory->angle.roll *= (trajectory->angleRate.roll);
        trajectory->angle.yaw *= (trajectory->angleRate.yaw);

        if (absPosition->horz < round(player->width / 2)) {
          // enforce our leftmost border
          absPosition->horz = round(player->width / 2);
          trajectory->position.horz = 0;
        }

        if (absPosition->vert < round(player->height / 2)) {
          // enforce our upper border
          absPosition->vert = round(player->height / 2);
          trajectory->position.vert = 0;
        }

        if (absPosition->horz > (scene->size->horz - round(player->width / 2))) {
          // enforce our rightmost border
          absPosition->horz = scene->size->horz - round(player->width / 2);
          trajectory->position.horz = 0;
        }

        if (absPosition->vert > (scene->size->vert - round(player->height / 2))) {
          // enforce our lower border
          absPosition->vert = scene->size->vert - round(player->height / 2);
          trajectory->position.vert = 0;
        }

        if (absPosition->horz > round(scene->view->size.horz / 2)
          && absPosition->horz < scene->size->horz - round(scene->view->size.horz / 2)
        ) {
          // moving horizontally around the center of our map
          position->horz = round(scene->view->size.horz / 2);
          scene->view->position.horz = absPosition->horz - round(scene->view->size.horz / 2);

        } else if (absPosition->horz < round(scene->view->size.horz / 2)) {
          // moving horizontally around the left border of our map
          position->horz = absPosition->horz;

        } else if (absPosition->horz > scene->size->horz - round(scene->view->size.horz / 2)) {
          // moving horizontally around the right border of our map
          position->horz = scene->view->size.horz - (scene->size->horz - absPosition->horz);
        }

        if (absPosition->vert > round(scene->view->size.vert / 2)
          && absPosition->vert < scene->size->vert - round(scene->view->size.vert / 2)
        ) {
          // moving vertically around the center of our map.
          position->vert = round(scene->view->size.vert / 2);
          scene->view->position.vert = absPosition->vert - round(scene->view->size.vert / 2);

        } else if (absPosition->vert < round(scene->view->size.vert / 2)) {
          // moving vertically around the upper border of our map.
          position->vert = absPosition->vert;

        } else if (absPosition->vert > scene->size->vert - round(scene->view->size.vert / 2)) {
          // moving vertically around the lower border of our map.
          position->vert = scene->view->size.vert - (scene->size->vert - absPosition->vert);
        }

        float horzRatio = 0.0;
        float vertRatio = 0.0;

        if (angle->pitch >= 180) {
          horzRatio = -(((270 - angle->pitch) / 90));
        } else {
          horzRatio = ((90 - angle->pitch) / 90);
        }

        if (angle->pitch <= 90) {
          vertRatio = (angle->pitch) / 90;
        } else if (angle->pitch > 270) {
          vertRatio = -(360 - angle->pitch) / 90;
        } else {
          vertRatio = (180 - angle->pitch) / 90;
        }

      //  if (KeyboardInput::isReleased(82)) {
      //    printf("stopping\n");
      //    player->setAction("standing_still");
      //  }

        if (KeyboardInput::isPressed(80)) {
          // turn left.
          player->setAction("turning_left");
          trajectory->angle.pitch -= 1;
        }

        if (KeyboardInput::isPressed(79)) {
          // turn right.
          player->setAction("turning_right");
          trajectory->angle.pitch += 1;
        }

        if (KeyboardInput::isPressed(82)) {
          // move forward.
          player->setAction("moving_forward");

          trajectory->position.horz += 1.5 * horzRatio;
          trajectory->position.vert += 1.5 * vertRatio;
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

              Position* bulletAbsolutePos = (Position*)bullet->state->get("absolute_position");
              bulletAbsolutePos->horz = (scene->size->horz / 2) - (scene->view->size.horz / 2) - (player->width / 2) + 20;
              bulletAbsolutePos->vert = (scene->size->vert / 2) - (scene->view->size.vert / 2) - (player->width / 2) + 20;

              Position* bulletPos = (Position*)bullet->state->get("position");
              Angle* bulletAngle = (Angle*)bullet->state->get("angle");
              Trajectory* bulletTraj = (Trajectory*)bullet->state->get("trajectory");

              bulletAngle->center.horz = angle->center.horz - 36;
              bulletAngle->center.vert = angle->center.vert - 36;

              bulletTraj->position.horz = 24 * horzRatio;
              bulletTraj->position.vert = 24 * vertRatio;

              bulletAbsolutePos->horz = absPosition->horz;
              bulletAbsolutePos->vert = absPosition->vert;

              bulletAngle->pitch = angle->pitch + 132;

              bullet->isActive = true;

              lastBulletTimestamp = SDL_GetTicks();

              break;
            }

          }

        }
        // keep angle within 360 degrees
        // TODO: enforce this from a state callback.
        angle->pitch = angle->pitch < 0 ? 360 - abs(angle->pitch) : angle->pitch;
        angle->pitch = angle->pitch >= 360 ? angle->pitch / 360 : angle->pitch;

        return (void*)NULL;
      }

  };

#endif
