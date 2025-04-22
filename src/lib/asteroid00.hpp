
#ifndef _GAME_ASTEROID00_HPP

  #define _GAME_ASTEROID00_HPP

  #include <time.h>
  #include <string.h>
  #include <stdlib.h>

  #include <core/keyboard.hpp>
  #include <core/image.hpp>
  #include <runtime/sprite.hpp>
  #include <runtime/data/trajectory.hpp>
  #include <runtime/data/position.hpp>
  #include <runtime/data/angle.hpp>
  #include <runtime/data/scale.hpp>
  #include <runtime/data/view.hpp>
  #include <scene.hpp>


  class Asteroid00: public SceneCharacter {

    public:

      static const uint32_t MAX_COUNT = 120;

      Asteroid00() {
        Trajectory* trajectory = (Trajectory*)this->state->get("trajectory");

        trajectory->positionRate->horz = 1.0;
        trajectory->positionRate->vert = 1.0;
        trajectory->positionRate->depth = 1.0;

        trajectory->angleRate->pitch = 1.0;
        trajectory->angleRate->roll = 1.0;
        trajectory->angleRate->yaw = 1.0;

        trajectory->scaleRate->horz = 0.0;
        trajectory->scaleRate->vert = 0.0;
        trajectory->scaleRate->depth = 0.0;

        this->isActive = true;
        this->type = "asteroid";

        //if (this->getIdentifier() == 0) {
        //  printf("IdentifierTools::generate(); %s\n", IdentifierTools::generate());
        //}

        //printf("(%s) identifier: %d\t/\tidentifierString: %s\n", this->type, this->getIdentifier(), this->getIdentifierString());
      }

      static Asteroid00* loadAssets(Scene* scene) {
        Asteroid00* asteroid = new Asteroid00();

        Sprite* sprite = new Sprite();
        Image* shipStandingStill = Image::load("./src/assets/asteroid_sheet.png", 44, 34, 57, 67);

        sprite->addFrame(shipStandingStill, 0);
        sprite->setLoop(false);

        asteroid->addSprite("standing_still", sprite);
        asteroid->setAction("standing_still");

        Scale* scale = (Scale*)asteroid->state->get("scale");
        Angle* angle = (Angle*)asteroid->state->get("angle");
        Position* absPosition = (Position*)asteroid->state->get("absolute_position");
        Trajectory* trajectory = (Trajectory*)asteroid->state->get("trajectory");

        uint32_t timestamp = SDL_GetTicks();

        srand(timestamp);

        //scale->horz = (rand() % 2) - 1;
        //scale->vert = (rand() % 2) - 1;

        angle->center->horz = 28;
        angle->center->vert = 33;

        absPosition->horz = rand() % (uint32_t)scene->size->horz;
        absPosition->vert = rand() % (uint32_t)scene->size->vert;

        trajectory->position->horz = ((float)(rand() % 3) / 2) - 1.5;
        trajectory->position->vert = ((float)(rand() % 3) / 2) - 1.5;

        trajectory->angle->pitch = ((float)(rand() % 3) / 2) - 1.5;
        trajectory->angle->roll = ((float)(rand() % 3) / 2) - 1.5;
        trajectory->angle->yaw = ((float)(rand() % 3) / 2) - 1.5;

        asteroid->onEvaluate(Asteroid00::evaluateCallback);
        asteroid->onCollision(Asteroid00::collisionCallback);

        return asteroid;
      }













      static void* collisionCallback(SceneBase* targ, Asteroid00* bullet, Scene* scene) {

        return NULL;
      }











      static void* evaluateCallback(Asteroid00* asteroid, Scene* scene) {
        Position* position = (Position*)asteroid->state->get("position");
        Angle* angle = (Angle*)asteroid->state->get("angle");
        Trajectory* trajectory = (Trajectory*)asteroid->state->get("trajectory");

        Position* absPosition = (Position*)asteroid->state->get("absolute_position");

        //absPosition->horz += trajectory->position->horz;
        //absPosition->vert += trajectory->position->vert;
        //absPosition->depth += trajectory->position->depth;

        angle->pitch += trajectory->angle->pitch;
        angle->roll += trajectory->angle->roll;
        angle->yaw += trajectory->angle->yaw;

        position->horz = absPosition->horz - scene->view->position.horz;
        position->vert = absPosition->vert - scene->view->position.vert;

        if (absPosition->horz < round(asteroid->width / 2)) {
          // enforce our leftmost border
          trajectory->position->horz = trajectory->position->horz * -1;
        }

        if (absPosition->vert < round(asteroid->height / 2)) {
          // enforce our upper border
          trajectory->position->vert = trajectory->position->vert * -1;
        }

        if (absPosition->horz > (scene->size->horz - round(asteroid->width / 2))) {
          // enforce our rightmost border
          trajectory->position->horz = trajectory->position->horz * -1;
        }

        if (absPosition->vert > (scene->size->vert - round(asteroid->height / 2))) {
          // enforce our lower border
          trajectory->position->vert = trajectory->position->vert * -1;
        }

        return NULL;
      }

  };

#endif
