
#ifndef _SCENE_CHARACTER_HPP

  #define _SCENE_CHARACTER_HPP

  #include "../core/dict.hpp"
  #include "../runtime/sprite.hpp"
  #include "../runtime/data/angle.hpp"
  #include "../runtime/data/position.hpp"
  #include "../scene/base.hpp"


  class SceneCharacter: public SceneBase {

    public:

      void evaluate() {
        Position* position = (Position*)this->state->get("position");
        Angle* angle = (Angle*)this->state->get("angle");
        Trajectory* trajectory = (Trajectory*)this->state->get("trajectory");



        Position* absolutePosition = (Position*)this->state->get("absolute_position");

        absolutePosition->horz += trajectory->position.horz;
        absolutePosition->vert += trajectory->position.vert;
        absolutePosition->depth += trajectory->position.depth;




        angle->pitch += trajectory->angle.pitch;
        angle->roll += trajectory->angle.roll;
        angle->yaw += trajectory->angle.yaw;

        trajectory->position.horz *= (trajectory->positionRate.horz);
        trajectory->position.vert *= (trajectory->positionRate.vert);
        trajectory->position.depth *= (trajectory->positionRate.depth);

        trajectory->angle.pitch *= (trajectory->angleRate.pitch);
        trajectory->angle.roll *= (trajectory->angleRate.roll);
        trajectory->angle.yaw *= (trajectory->angleRate.yaw);

        unsigned long int charId = this->identifier;
        const char* hookId = Hook::generateIdentifier(charId, "onEvaluate");

        this->executeCallback(hookId, (void*)this);
      }

  };

#endif
