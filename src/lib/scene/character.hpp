
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
        Position position = { 0, 0, 0 };
        Scale scale = { 1.0, 1.0, 1.0 };
        Angle angle = { 0.0, { 0, 0, 0 } };

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
