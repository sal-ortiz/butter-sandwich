
#ifndef _SCENE_BACKGROUND_HPP

  #define _SCENE_BACKGROUND_HPP

  #include "../core/dict.hpp"
  #include "../runtime/sprite.hpp"
  #include "../scene/base.hpp"


  class SceneBackground: public SceneBase {

    public:

      void evaluate() {
        Trajectory* trajectory = (Trajectory*)this->state->get("trajectory");
        View* view = (View*)this->state->get("view");

        view->position.horz += trajectory->position.horz;
        view->position.vert += trajectory->position.vert;
        view->position.depth += trajectory->position.depth;

        trajectory->position.horz *= trajectory->positionRate.horz;
        trajectory->position.vert *= trajectory->positionRate.vert;
        trajectory->position.depth *= trajectory->positionRate.depth;

        unsigned long int charId = this->identifier;
        const char* hookId = Hook::generateIdentifier(charId, "onEvaluate");

        this->executeCallback(hookId, (void*)this);
      }

  };

#endif
