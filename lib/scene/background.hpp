
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

      State state;
      Dict<Sprite*> sprites;

      Position* position;
      Scale* scale;
      View* view;

      const char* action;

      void*(*evalCallback)(void*);


      SceneBackground() {
        this->evalCallback = NULL;
        this->identifier = SceneBackground::generateIdentifier();

        this->position = new Position(0, 0, 0);
        this->scale = new Scale(0.0, 0.0, 0.0);
        this->view = new View(0, 0, 0, 0, 0, 0);
      }

      void setAction(const char* curAction) {
        this->action = curAction;
      }

      void addSprite(const char* actionId, Sprite* sprite) {
        sprites.set(actionId, sprite);
      }

      void render(SDL_Renderer* renderer) {
        const char* actionId = this->action;

        Scale* scale = this->scale;

        Sprite* sprite = sprites.get(actionId);

        sprite->render(
          renderer,
          this->position->horz,
          this->position->vert,
          this->view->position.horz,
          this->view->position.vert,
          this->view->size.horz,
          this->view->size.vert
        );
      }

      void evaluate() {
        unsigned long int charId = this->identifier;
        const char* hookId = Hook::generateIdentifier(charId, "onEvaluate");

        this->executeCallback(hookId, (void*)this);
      }

      void onEvaluate(void*(*callback)(void*, void*)) {
        unsigned long int charId = this->identifier;
        const char* hookId = Hook::generateIdentifier(charId, "onEvaluate");

        this->on(hookId, callback, NULL);
      }

  };

#endif
