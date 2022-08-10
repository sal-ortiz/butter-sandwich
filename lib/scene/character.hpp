
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

      State state;
      Dict<Sprite*> sprites;

      Position* position;
      Angle* angle;
      Scale* scale;
      View* view;

      Trajectory* trajectory;

      // TODO: hack: find a better way to serve these values.
      float width;
      float height;

      const char* action;

      void*(*evalCallback)(void*);


      SceneCharacter() {
        this->evalCallback = NULL;
        this->identifier = SceneCharacter::generateIdentifier();

        this->position = new Position(0, 0, 0);
        this->angle = new Angle(0.0, 0.0, 0.0, 0, 0, 0);
        this->scale = new Scale(0.0, 0.0, 0.0);
        this->view = new View(0, 0, 0, 0, 0, 0);
        this->trajectory = new Trajectory();

        //this->trajectory->positionRate.horz = 0.9;
        //this->trajectory->positionRate.vert = 0.9;
        //this->trajectory->positionRate.depth = 0.0;

        this->trajectory->position.horz = 0;
        this->trajectory->position.vert = 0;
        this->trajectory->position.depth = 0;

        this->trajectory->scale.horz = 0;
        this->trajectory->scale.vert = 0;
        this->trajectory->scale.depth = 0;

        this->trajectory->angle.pitch = 0;
        this->trajectory->angle.roll = 0;
        this->trajectory->angle.yaw = 0;

        //this->trajectory->positionRate.horz = 100;
        //this->trajectory->positionRate.vert = 100;
        //this->trajectory->positionRate.depth = 100;

        //this->trajectory->angleRate.pitch = 100;
        //this->trajectory->angleRate.roll = 100;
        //this->trajectory->angleRate.yaw = 100;

        //this->trajectory->scaleRate.horz = 100;
        //this->trajectory->scaleRate.vert = 100;
        //this->trajectory->scaleRate.depth = 100;




        //state.set("scale", (void*)this->scale);
        //state.set("angle", (void*)this->angle);
        //state.set("size", (void*)this->size);
        //state.set("trajectory", (void*)this->trajectory);
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

        Position* position = this->position;
        Angle* angle = this->angle;
        Scale* scale = this->scale;
        View* view = this->view;

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
          view->size.vert,
          angle->pitch,
          angle->center.horz,
          angle->center.vert
        );

      }

      void evaluate() {


        this->position->horz += this->trajectory->position.horz;
        this->position->vert += this->trajectory->position.vert;
        this->position->depth += this->trajectory->position.depth;

        this->angle->pitch += this->trajectory->angle.pitch;
        this->angle->roll += this->trajectory->angle.roll;
        this->angle->yaw += this->trajectory->angle.yaw;

        //this->scale->horz += this->trajectory->scale.horz;
        //this->scale->vert += this->trajectory->scale.vert;
        //this->scale->depth += this->trajectory->scale.depth;


        this->trajectory->position.horz *= (this->trajectory->positionRate.horz);
        this->trajectory->position.vert *= (this->trajectory->positionRate.vert);
        this->trajectory->position.depth *= (this->trajectory->positionRate.depth);

        this->trajectory->angle.pitch *= (this->trajectory->angleRate.pitch);
        this->trajectory->angle.roll *= (this->trajectory->angleRate.roll);
        this->trajectory->angle.yaw *= (this->trajectory->angleRate.yaw);

        //this->trajectory->scale.horz *= (this->trajectory->scaleRate.horz);
        //this->trajectory->scale.vert *= (this->trajectory->scaleRate.vert);
        //this->trajectory->scale.depth *= (this->trajectory->scaleRate.depth);




        unsigned long int charId = this->identifier;
        const char* hookId = Hook::generateIdentifier(charId, "onEvaluate");

        this->executeCallback(hookId, (void*)this);




      }

      void onEvaluate(void*(*callback)(void*, void*), void* data) {
        unsigned long int charId = this->identifier;
        const char* hookId = Hook::generateIdentifier(charId, "onEvaluate");

        this->on(hookId, callback, data);
      }

  };

#endif
