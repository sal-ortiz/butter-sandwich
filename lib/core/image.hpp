
#ifndef _IMAGE_HPP

  #define _IMAGE_HPP

  #include <assert.h>

  #include <SDL2/SDL.h>
  #include <SDL2/SDL_image.h>


  class Image {

    private:

      SDL_Surface* surface;


    public:

      SDL_Rect view;


      Image() {
        this->surface = NULL;
      }

      ~Image() {
        SDL_FreeSurface(surface);
      }

      static Image* load(const char* filename, uint16_t viewX, uint16_t viewY, uint16_t viewW=0, uint16_t viewH=0) {
        Image* img = new Image();

        img->surface = SDL_LoadBMP(filename);
        img->view = { viewX, viewY, viewW, viewH };

        return img;
      }

      void render(
        SDL_Renderer* renderer,
        uint32_t dstX,
        uint32_t dstY,
        uint32_t srcX,
        uint32_t srcY,
        uint32_t srcWidth,
        uint32_t srcHeight,
        float dstAngle=0.0,
        uint32_t centerX=0,
        uint32_t centerY=0
      ) {
        //int imgWidth, imgHeight;

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, this->surface);
        //SDL_QueryTexture(texture, NULL, NULL, &imgWidth, &imgHeight);

        SDL_Rect dstRect = {
          (uint16_t)dstX,
          (uint16_t)dstY,
          (uint16_t)srcWidth,
          (uint16_t)srcHeight,
        };

        SDL_Rect srcRect = {
          (uint16_t)srcX,
          (uint16_t)srcY,
          (uint16_t)srcWidth,
          (uint16_t)srcHeight
        };

        SDL_Point center = {
          (int16_t)centerX,
          (uint16_t)centerY
        };

        if (srcRect.x == 0) {
          srcRect.x = this->view.x;
        }

        if (srcRect.y == 0) {
          srcRect.y = this->view.y;
        }

        if (srcRect.w == 0) {
          srcRect.w = this->view.w;
        }

        if (srcRect.h == 0) {
          srcRect.h = this->view.h;
        }

        dstRect.w = srcRect.w;
        dstRect.h = srcRect.h;

        SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, dstAngle, &center, SDL_FLIP_NONE);

        SDL_DestroyTexture(texture);
      }

  };


#endif
