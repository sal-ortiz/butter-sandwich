
#ifndef _SCENE_BACKGROUND_HPP

  #define _SCENE_BACKGROUND_HPP

  #include "../core/dict.hpp"
  #include "../core/data/position.hpp"
  #include "../core/data/scale.hpp"
  #include "../core/data/view.hpp"

  #include "../runtime/state.hpp"
  #include "../runtime/sprite.hpp"

  #include "../scene/base.hpp"


  class SceneBackground: public SceneBase {

    public:

      Dict<Sprite*> sprites;

      View* view;


      // TODO: hack: find a better way to serve these values.
      float width;
      float height;

      const char* action;

      void*(*evalCallback)(void*);


      SceneBackground() {
        this->evalCallback = NULL;
        this->identifier = SceneBackground::generateIdentifier();

        Trajectory* trajectory = (Trajectory*)this->state->get("trajectory");

        this->view = new View(0, 0, 0, 0, 0, 0);
      }

      void setAction(const char* curAction) {
        Sprite* curSprite = sprites.get(curAction);

        this->action = curAction;
        this->width = curSprite->width;
        this->height = curSprite->height;
      }

      void addSprite(const char* actionId, Sprite* sprite) {
        sprites.set(actionId, sprite);
      }

      void render(SDL_Renderer* renderer) {
        const char* actionId = this->action;

        Angle* angle = (Angle*)this->state->get("angle");
        Scale* scale = (Scale*)this->state->get("scale");
        View* view = this->view;
        Position* position = (Position*)this->state->get("position");


        Sprite* sprite = sprites.get(actionId);

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
          view->size.vert
        );
      }

      void evaluate() {
        Trajectory* trajectory = (Trajectory*)this->state->get("trajectory");

        this->view->position.horz += trajectory->position.horz;
        this->view->position.vert += trajectory->position.vert;
        this->view->position.depth += trajectory->position.depth;

        trajectory->position.horz *= trajectory->positionRate.horz;
        trajectory->position.vert *= trajectory->positionRate.vert;
        trajectory->position.depth *= trajectory->positionRate.depth;

        unsigned long int charId = this->identifier;
        const char* hookId = Hook::generateIdentifier(charId, "onEvaluate");

        //this->executeCallback(hookId, (void*)this);
      }

      void onEvaluate(void*(*callback)(void*, void*), void* data) {
        unsigned long int charId = this->identifier;
        const char* hookId = Hook::generateIdentifier(charId, "onEvaluate");

        this->on(hookId, callback, data);
      }

  };

#endif
