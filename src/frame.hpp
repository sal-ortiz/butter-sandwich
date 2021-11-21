
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

      void render(SDL_Renderer* renderer, uint32_t dstX, uint32_t dstY) {
        SDL_Rect dstRect = { dstX, dstY, NULL, NULL };


        this->image->render(renderer, dstRect);
      }

      Image* getImage() {
        return image;
      }

  };


#endif
