
#ifndef _GAME_ASTEROID00_HPP

  #define _GAME_ASTEROID00_HPP

  #include <time.h>
  #include <string.h>
  #include <stdlib.h>

  #include "../../lib/core/keyboard.hpp"
  #include "../../lib/core/image.hpp"
  #include "../../lib/runtime/sprite.hpp"
  #include "../../lib/runtime/data/trajectory.hpp"
  #include "../../lib/runtime/data/position.hpp"
  #include "../../lib/runtime/data/angle.hpp"
  #include "../../lib/runtime/data/scale.hpp"
  #include "../../lib/runtime/data/view.hpp"
  #include "../../lib/scene.hpp"


  class Asteroid00: public SceneCharacter {

    public:

      Asteroid00() {
        Trajectory* trajectory = (Trajectory*)this->state->get("trajectory");

        trajectory->positionRate.horz = 1.0;
        trajectory->positionRate.vert = 1.0;
        trajectory->positionRate.depth = 1.0;

        trajectory->angleRate.pitch = 1.0;
        trajectory->angleRate.roll = 1.0;
        trajectory->angleRate.yaw = 1.0;

        trajectory->scaleRate.horz = 0.0;
        trajectory->scaleRate.vert = 0.0;
        trajectory->scaleRate.depth = 0.0;

        this->isActive = true;
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

        scale->horz = 1.0;
        scale->vert = 1.0;

        angle->center.horz = 28;
        angle->center.vert = 33;

        time_t timestamp = time(NULL);

        srand(timestamp);

        absPosition->horz = rand() % (unsigned long int)scene->size->horz;
        absPosition->vert = rand() % (unsigned long int)scene->size->vert;

        trajectory->position.horz = ((float)(rand() % 5) / 2) - 2.5;
        trajectory->position.vert = ((float)(rand() % 5) / 2) - 2.5;

        trajectory->angle.pitch = ((float)(rand() % 3) / 2) - 1.5;
        trajectory->angle.roll = ((float)(rand() % 3) / 2) - 1.5;
        trajectory->angle.yaw = ((float)(rand() % 3) / 2) - 1.5;

        asteroid->onEvaluate(Asteroid00::evaluateCallback, scene);

        return asteroid;
      }

      static void* evaluateCallback(void* inp, void* dataOne, void* dataTwo) {
        Asteroid00* asteroid = reinterpret_cast<Asteroid00*>(inp);
        Scene* scene = reinterpret_cast<Scene*>(dataOne);

        Position* position = (Position*)asteroid->state->get("position");
        Angle* angle = (Angle*)asteroid->state->get("angle");
        Trajectory* trajectory = (Trajectory*)asteroid->state->get("trajectory");

        Position* absPosition = (Position*)asteroid->state->get("absolute_position");

        absPosition->horz += trajectory->position.horz;
        absPosition->vert += trajectory->position.vert;
        absPosition->depth += trajectory->position.depth;

        angle->pitch += trajectory->angle.pitch;
        angle->roll += trajectory->angle.roll;
        angle->yaw += trajectory->angle.yaw;

        //trajectory->position.horz *= (trajectory->positionRate.horz);
        //trajectory->position.vert *= (trajectory->positionRate.vert);
        //trajectory->position.depth *= (trajectory->positionRate.depth);

        //trajectory->angle.pitch *= (trajectory->angleRate.pitch);
        //trajectory->angle.roll *= (trajectory->angleRate.roll);
        //trajectory->angle.yaw *= (trajectory->angleRate.yaw);

        position->horz = absPosition->horz - scene->view->position.horz;
        position->vert = absPosition->vert - scene->view->position.vert;

        if (absPosition->horz < round(asteroid->width / 2)) {
          // enforce our leftmost border
          trajectory->position.horz = trajectory->position.horz * -1;
        }

        if (absPosition->vert < round(asteroid->height / 2)) {
          // enforce our upper border
          trajectory->position.vert = trajectory->position.vert * -1;
        }

        if (absPosition->horz > (scene->size->horz - round(asteroid->width / 2))) {
          // enforce our rightmost border
          trajectory->position.horz = trajectory->position.horz * -1;
        }

        if (absPosition->vert > (scene->size->vert - round(asteroid->height / 2))) {
          // enforce our lower border
          trajectory->position.vert = trajectory->position.vert * -1;
        }

        //printf("\n\n=========================================================");
        //printf("\n[%u] POSITION: (%f, %f)", SDL_GetTicks(), absPosition->horz, absPosition->vert);
        //printf("\n[%u] ANGLE TRAJ: %f", SDL_GetTicks(), trajectory->angle.pitch);
        //printf("\n[%u] POSITION TRAJ: (%f, %f)", SDL_GetTicks(), trajectory->position.horz, trajectory->position.vert);
        //printf("\n=========================================================\n\n");

        return (void*)NULL;
      }

  };

#endif
