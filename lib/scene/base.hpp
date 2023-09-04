
#ifndef _SCENE_BASE_HPP

  #define _SCENE_BASE_HPP

  #include "../core/dict.hpp"
  #include "../runtime/base.hpp"
  #include "../runtime/sprite.hpp"
  #include "../runtime/state.hpp"
  #include "../runtime/data/position.hpp"
  #include "../runtime/data/angle.hpp"
  #include "../runtime/data/scale.hpp"
  #include "../runtime/data/view.hpp"
  #include "../runtime/data/trajectory.hpp"


  class SceneBase: public RuntimeBase {

    private:

      void*(*evalCallback)(void*);

      const char* action;
      Dict<Sprite*> sprites;


    public:

      State* state;

      const char* name;
      const char* type;

      // TODO: hack: find a better way to serve these values.
      unsigned long int width;
      unsigned long int height;

      bool isActive;

      SceneBase() {
        this->evalCallback = NULL;

        this->state = new State();

        this->state->set("position", new Position());
        this->state->set("angle", new Angle());
        this->state->set("scale", new Scale());
        this->state->set("view", new View());
        this->state->set("trajectory", new Trajectory());

        this->state->set("absolute_position", new Position());
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

      void setName(const char* name) {
        this->name = name;
      }

      const char* getName() {
        return this->name;
      }

      void setType(const char* type) {
        this->type = type;
      }

      const char* getType() {
        return this->type;
      }

      void onCollision(void*(*callback)(void*, void*, void*), void* dataOne=NULL, void* dataTwo=NULL) {
        unsigned long int charId = this->getIdentifier();
        const char* hookId = Hook::generateIdentifier(charId, "onCollision");

        this->on(hookId, callback, dataOne, dataTwo);
      }

      void onEvaluate(void*(*callback)(void*, void*, void*), void* dataOne=NULL, void* dataTwo=NULL) {
        unsigned long int charId = this->getIdentifier();
        const char* hookId = Hook::generateIdentifier(charId, "onEvaluate");

        this->on(hookId, callback, dataOne, dataTwo);
      }

      void render(SDL_Renderer* renderer) {
        const char* actionId = this->action;

        Position* position = (Position*)this->state->get("position");
        Angle* angle = (Angle*)this->state->get("angle");
        Scale* scale = (Scale*)this->state->get("scale");
        View* view = (View*)this->state->get("view");

        Sprite* sprite = this->sprites.get(actionId);

        this->width = sprite->width;
        this->height = sprite->height;

        sprite->render(renderer, position, view, angle, scale);
      }

      void evaluate() {
        unsigned long int charId = this->getIdentifier();
        const char* hookId = Hook::generateIdentifier(charId, "onEvaluate");

        this->executeCallback(hookId, (void*)this);
      }

  };

#endif
