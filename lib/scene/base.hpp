
#ifndef _SCENE_BASE_HPP

  #define _SCENE_BASE_HPP

  #include "../core/dict.hpp"
  #include "../runtime/base.hpp"
  #include "../runtime/state.hpp"
  #include "../runtime/data/position.hpp"
  #include "../runtime/data/angle.hpp"
  #include "../runtime/data/scale.hpp"
  #include "../runtime/data/view.hpp"
  #include "../runtime/data/trajectory.hpp"


  class SceneBase: public RuntimeBase {

    protected:

      void*(*evalCallback)(void*);

      const char* action;
      Dict<Sprite*> sprites;


    public:

      State* state;

      // TODO: hack: find a better way to serve these values.
      unsigned long int width;
      unsigned long int height;


      SceneBase() {
        this->identifier = RuntimeBase::generateIdentifier();
        this->evalCallback = NULL;

        this->state = new State();

        this->state->set("position", new Position());
        this->state->set("angle", new Angle());
        this->state->set("scale", new Scale());
        this->state->set("view", new View());
        this->state->set("trajectory", new Trajectory());
      }

      void addSprite(const char* actionId, Sprite* sprite) {
        this->sprites.set(actionId, sprite);
      }

      void setAction(const char* curAction) {
        Sprite* curSprite = this->sprites.get(curAction);

        this->action = curAction;
        this->width = curSprite->width;
        this->height = curSprite->height;
      }

      void onEvaluate(void*(*callback)(void*, void*), void* data) {
        unsigned long int charId = this->identifier;
        const char* hookId = Hook::generateIdentifier(charId, "onEvaluate");

        this->on(hookId, callback, data);
      }

      void render(SDL_Renderer* renderer) {
        const char* actionId = this->action;

        Position* position = (Position*)this->state->get("position");
        Angle* angle = (Angle*)this->state->get("angle");
        Scale* scale = (Scale*)this->state->get("scale");
        View* view = (View*)this->state->get("view");

        Sprite* sprite = this->sprites.get(actionId);

        // TODO: hack: find a better place to set these values.
        this->width = sprite->width;
        this->height = sprite->height;

        sprite->render(renderer, position, view, angle, scale);
      }

      void evaluate() {
        unsigned long int charId = this->identifier;
        const char* hookId = Hook::generateIdentifier(charId, "onEvaluate");

        this->executeCallback(hookId, (void*)this);
      }

  };

#endif
