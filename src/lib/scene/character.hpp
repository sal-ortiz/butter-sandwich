
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

      SceneCharacter() {
        Position position;
        position.horz = 0;
        position.vert = 0;

        Scale scale;
        scale.horz = 0;
        scale.vert = 0;

        Angle angle;
        angle.pitch = 0.0;
        angle.center.horz = 0;
        angle.center.vert = 0;
        angle.center.depth = 0;

        state.set("position", (void*)&position);
        state.set("scale", (void*)&scale);
        state.set("angle", (void*)&angle);
      }

      void addSprite(const char* actionId, Sprite* sprite) {
        sprites.set(actionId, sprite);
      }

      void render(const char* actionId, SDL_Renderer* renderer) {
        Sprite* sprite = sprites.get(actionId);

        sprite->render(renderer, 0, 0);
      }

      void evaluate() {

      }


  };

#endif
