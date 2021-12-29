
#ifndef _SPRITE_FRAME_HPP
  #define _SPRITE_FRAME_HPP

  #include "./runtime/image.hpp"


  class SpriteFrame {

    private:

      Image* image;


    public:

      SpriteFrame() {
        this->image = NULL;
      }

      void render(SDL_Renderer* renderer, uint16_t dstX, uint16_t dstY) {
        SDL_Rect dstRect = { dstX, dstY, 0, 0 };

        if (this->image) {
          this->image->render(renderer, dstRect);
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
