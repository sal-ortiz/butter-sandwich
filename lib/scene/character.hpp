
#ifndef _SCENE_CHARACTER_HPP

  #define _SCENE_CHARACTER_HPP

  #include "../core/dict.hpp"
  #include "../core/data/position.hpp"
  #include "../core/data/angle.hpp"
  #include "../core/data/scale.hpp"
  #include "../core/data/size.hpp"
  #include "../core/data/view.hpp"
  #include "../core/data/trajectory.hpp"

  #include "../runtime/state.hpp"
  #include "../runtime/sprite.hpp"

  #include "../scene/base.hpp"


  class SceneCharacter: public SceneBase {

    public:

      SceneCharacter() {
        this->identifier = SceneCharacter::generateIdentifier();
      }

      void evaluate() {

        Position* position = (Position*)this->state->get("position");
        Angle* angle = (Angle*)this->state->get("angle");
        Trajectory* trajectory = (Trajectory*)this->state->get("trajectory");

        position->horz += trajectory->position.horz;
        position->vert += trajectory->position.vert;
        position->depth += trajectory->position.depth;

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

      void setAction(const char* curAction) {
        Sprite* curSprite = sprites.get(curAction);

        this->action = curAction;
        this->width = curSprite->width;
        this->height = curSprite->height;
      }

  };

#endif
