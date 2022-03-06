
#ifndef _SCENE_CHARACTER_HPP

  #define _SCENE_CHARACTER_HPP

  #include "../core/dict.hpp"
  #include "../runtime/state.hpp"
  #include "../runtime/sprite.hpp"

  #include "../core/data/position.hpp"
  #include "../core/data/angle.hpp"
  #include "../core/data/scale.hpp"

  class SceneCharacter {

    public:

      State state;
      Dict<Sprite*> sprites;

      Position* position;
      Angle* angle;
      Scale* scale;

      SceneCharacter() {
        this->position = new Position(0, 0, 0);
        this->angle = new Angle(0.0, 0.0, 0.0, 0, 0, 0);
        this->scale = scale = new Scale(0.0, 0.0, 0.0);

        state.set("position", (void*)this->position);
        state.set("scale", (void*)this->scale);
        state.set("angle", (void*)this->angle);
      }

      void addSprite(const char* actionId, Sprite* sprite) {
        sprites.set(actionId, sprite);
      }

      void render(const char* actionId, SDL_Renderer* renderer) {
        Sprite* sprite = sprites.get(actionId);

        Position* pos = this->position;
        Angle* angle = this->angle;
        Scale* scale = this->scale;

        sprite->render(
          renderer,
          pos->horz,
          pos->vert,
          angle->pitch,
          angle->center.horz,
          angle->center.vert
        );
      }

      void evaluate() {

      }

  };

#endif
