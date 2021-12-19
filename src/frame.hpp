
#ifndef _SPRITE_FRAME_HPP
  #define _SPRITE_FRAME_HPP

  #include "./runtime/image.hpp"

  class SpriteFrame {

    private:

      Image* image;

    public:

      SpriteFrame(Image* img) {
        this->image = img;
      }

      void render(SDL_Renderer* renderer, uint16_t dstX, uint16_t dstY) {
        SDL_Rect dstRect = { dstX, dstY, 0, 0 };


        this->image->render(renderer, dstRect);
      }

      Image* getImage() {
        return image;
      }

  };


#endif
