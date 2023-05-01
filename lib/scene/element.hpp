


#ifndef _SCENE_ELEMENT_HPP

  #define _SCENE_ELEMENT_HPP

  #include "../core/dict.hpp"
  #include "../runtime/sprite.hpp"
  #include "../scene/base.hpp"


  class SceneElement: public SceneBase {

    public:

      void evaluate() {
        Trajectory* trajectory = (Trajectory*)this->state->get("trajectory");
        Position* position = (Position*)this->state->get("position");
        Position* absolutePosition = (Position*)this->state->get("absolute_position");






        absolutePosition->horz += trajectory->position.horz;
        absolutePosition->vert += trajectory->position.vert;
        absolutePosition->depth += trajectory->position.depth;







        //trajectory->position.horz *= (trajectory->positionRate.horz);
        //trajectory->position.vert *= (trajectory->positionRate.vert);
        //trajectory->position.depth *= (trajectory->positionRate.depth);







        unsigned long int charId = this->identifier;
        const char* hookId = Hook::generateIdentifier(charId, "onEvaluate");

        this->executeCallback(hookId, (void*)this);
      }

  };

#endif
