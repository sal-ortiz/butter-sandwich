

#ifndef _SCENE_BASE_HPP_

  #define _SCENE_BASE_HPP_

  #include "../runtime/base.hpp"


  class SceneBase: public RuntimeBase {


    private:

      void*(*evalCallback)(void*);


    protected:

      const char* action;
      Dict<Sprite*> sprites;


    public:

      State* state;

      unsigned long int width;
      unsigned long int height;

      SceneBase() {
        this->generateIdentifier();

        this->evalCallback = NULL;
        this->state = new State();

        this->state->set("position", new Position());
        this->state->set("angle", new Angle());
        this->state->set("scale", new Scale());
        this->state->set("view", new View());
        this->state->set("trajectory", new Trajectory());
      }

      void addSprite(const char* actionId, Sprite* sprite) {
        sprites.set(actionId, sprite);
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

        sprite->render(
          renderer,
          position->horz,
          position->vert,
          view->position.horz,
          view->position.vert,
          view->size.horz,
          view->size.vert,
          angle->pitch,
          angle->center.horz,
          angle->center.vert
        );

      }

  };



#endif
