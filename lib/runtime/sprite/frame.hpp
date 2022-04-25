
#ifndef _SPRITE_FRAME_HPP

  #define _SPRITE_FRAME_HPP

  #include "../../core/image.hpp"
  #include "../../core/data/position.hpp"
  #include "../../core/data/angle.hpp"
  #include "../../core/data/view.hpp"


  class SpriteFrame {

    private:

      Image* image;


    public:

      SpriteFrame() {
        this->image = NULL;
      }

      void render(SDL_Renderer* renderer, Position dstPos, View srcView, Angle angle) {
        SDL_Rect dstRect = {
          (uint16_t)dstPos.horz,
          (uint16_t)dstPos.vert,
          (uint16_t)srcView.size.horz,
          (uint16_t)srcView.size.vert
        };

        SDL_Rect srcRect = {
          (uint16_t)srcView.position.horz, (uint16_t)srcView.position.vert,
          (uint16_t)srcView.size.horz, (uint16_t)srcView.size.horz
        };

        SDL_Point center = { (int16_t)angle.center.horz, (uint16_t)angle.center.vert };

        if (this->image) {

          this->image->render(
            renderer,
            dstRect,
            srcRect,
            angle.pitch,
            center
          );
        }

      }

      void setImage(Image* img) {
        this->image = img;
      }

      Image* getImage() {
        return this->image;
      }

  };

#endif
