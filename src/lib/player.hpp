
#ifndef _GAME_PLAYER_HPP

  #define _GAME_PLAYER_HPP

  #include <string.h>

  #include <core/keyboard.hpp>
  #include <core/image.hpp>
  #include <runtime/sprite.hpp>
  #include <runtime/data/trajectory.hpp>
  #include <runtime/data/position.hpp>
  #include <runtime/data/angle.hpp>
  #include <runtime/data/scale.hpp>
  #include <runtime/data/view.hpp>
  #include <scene.hpp>


  static uint32_t lastBulletTimestamp = 0;

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

        trajectory->colorRate.red = 10.0;
        trajectory->colorRate.green = 10.0;
        trajectory->colorRate.blue = 10.0;
        trajectory->colorRate.alpha = 10.0;

        //printf("(%s) identifier: %d\t/\tidentifierString: %s\n", this->type, this->getIdentifier(), this->getIdentifierString());

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

        Color* color = (Color*)player->state->get("color");
        Scale* scale = (Scale*)player->state->get("scale");
        Angle* angle = (Angle*)player->state->get("angle");
        Position* absPosition = (Position*)player->state->get("absolute_position");

        scale->horz = 1.0;
        scale->vert = 1.0;

        angle->center->horz = 43;
        angle->center->vert = 43;

        absPosition->horz = scene->size->horz / 2;
        absPosition->vert = scene->size->vert / 2;

        color->red = 1.0;
        color->green = 1.0;
        color->blue = 1.0;
        color->alpha = 1.0;

        player->onEvaluate(Player::evaluateCallback);
        player->onCollision(Player::collisionCallback);

        return player;
      }

      static void* collisionCallback(SceneBase* tag, Player* player, Scene* scene) {

        printf("\n[%u] PLAYER COLLISION!!", SDL_GetTicks());
        //printf("\ntarg->name: %s", targ->name);
        //printf("\nplayer->name: %s", player->name);
        //printf("\nscene->size->horz / scene->size->vert: %d / %d", scene->size->horz, scene->size->vert);

        //printf("\n");

        return NULL;
      }

      static void* evaluateCallback(Player* player, Scene* scene) {
        Position* position = (Position*)player->state->get("position");
        Angle* angle = (Angle*)player->state->get("angle");
        Color* color = (Color*)player->state->get("color");
        Trajectory* trajectory = (Trajectory*)player->state->get("trajectory");

        Position* absPosition = (Position*)player->state->get("absolute_position");

        absPosition->horz += trajectory->position.horz;
        absPosition->vert += trajectory->position.vert;
        absPosition->depth += trajectory->position.depth;

        angle->pitch += trajectory->angle.pitch;
        angle->roll += trajectory->angle.roll;
        angle->yaw += trajectory->angle.yaw;

        color->red = trajectory->color.red;
        color->green = trajectory->color.green;
        color->blue = trajectory->color.blue;
        color->alpha = trajectory->color.alpha;

        trajectory->position.horz *= (trajectory->positionRate.horz);
        trajectory->position.vert *= (trajectory->positionRate.vert);
        trajectory->position.depth *= (trajectory->positionRate.depth);

        trajectory->angle.pitch *= (trajectory->angleRate.pitch);
        trajectory->angle.roll *= (trajectory->angleRate.roll);
        trajectory->angle.yaw *= (trajectory->angleRate.yaw);

        trajectory->color.red += ((1 + trajectory->color.red) * trajectory->colorRate.red) / 36;
        trajectory->color.green += ((1 + trajectory->color.green) * trajectory->colorRate.green) / 36;
        trajectory->color.blue += ((1 + trajectory->color.blue) * trajectory->colorRate.blue) / 36;
        trajectory->color.alpha += ((1 + trajectory->color.alpha) * trajectory->colorRate.alpha) / 36;


        if (trajectory->color.red > 255)    trajectory->color.red = 255;
        if (trajectory->color.blue > 255)   trajectory->color.blue = 255;
        if (trajectory->color.green > 255)  trajectory->color.green = 255;
        if (trajectory->color.alpha > 255)  trajectory->color.alpha = 255;

        if (absPosition->horz < round(player->width / 2) + 6) { // +6 tweak
          // enforce our leftmost border
          absPosition->horz = round(player->width / 2) + 6;     // +6 tweak
          trajectory->position.horz = 0;
        }

        if (absPosition->vert < round(player->height / 2) + 6) {  // +6 tweak
          // enforce our upper border
          absPosition->vert = round(player->height / 2) + 6;      // +6 tweak
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

        if (KeyboardInput::isPressed(80) || KeyboardInput::isHeld(80)) {
          // turn left.
          player->setAction("turning_left");
          trajectory->angle.pitch -= 1;
        }

        if (KeyboardInput::isPressed(79) || KeyboardInput::isHeld(79)) {
          // turn right.
          player->setAction("turning_right");
          trajectory->angle.pitch += 1;
        }

        if (KeyboardInput::isPressed(82) || KeyboardInput::isHeld(82)) {
          // move forward.
          player->setAction("moving_forward");

          trajectory->position.horz += 1.5 * horzRatio;
          trajectory->position.vert += 1.5 * vertRatio;
        }

        if (
          KeyboardInput::isReleased(79) ||  // right
          KeyboardInput::isReleased(80) ||  // left
          KeyboardInput::isReleased(82)     // forward
        ) {
          // standing still.
          player->setAction("standing_still");
        }

        if ((KeyboardInput::isPressed(44) || KeyboardInput::isHeld(44))
          && (SDL_GetTicks() - lastBulletTimestamp) > Bullet::DELAY
        ) {
          // fire a pellet

          for (uint32_t bulletIdx = 0; bulletIdx < scene->getNumElements(); bulletIdx++) {
            char* name = new char();

            sprintf(name, "bullet-%.2u", bulletIdx);

            SceneElement* element = (SceneElement*)scene->getElement(name);

            if (element == NULL) {
              continue;
            }

            int32_t typeCmpRes = strcmp(element->getType(), "bullet");

            if (element->isActive == false && typeCmpRes == 0) {
              Bullet* bullet = reinterpret_cast<Bullet*>(element);

              Position* bulletAbsolutePos = (Position*)bullet->state->get("absolute_position");
              bulletAbsolutePos->horz = (scene->size->horz / 2) - (scene->view->size.horz / 2) - (player->width / 2) + 20;
              bulletAbsolutePos->vert = (scene->size->vert / 2) - (scene->view->size.vert / 2) - (player->width / 2) + 20;

              Position* bulletPos = (Position*)bullet->state->get("position");
              Angle* bulletAngle = (Angle*)bullet->state->get("angle");
              Trajectory* bulletTraj = (Trajectory*)bullet->state->get("trajectory");

              bulletAngle->center->horz = angle->center->horz - 36;
              bulletAngle->center->vert = angle->center->vert - 36;

              bulletTraj->position.horz = 24 * horzRatio;
              bulletTraj->position.vert = 24 * vertRatio;

              bulletAbsolutePos->horz = absPosition->horz;
              bulletAbsolutePos->vert = absPosition->vert;

              bulletAngle->pitch = angle->pitch + 132;

              bullet->isActive = true;

              lastBulletTimestamp = SDL_GetTicks();

              bulletTraj->color.red = 120;
              bulletTraj->color.green = 10;
              bulletTraj->color.blue = 10;
              bulletTraj->color.alpha = 100;

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
