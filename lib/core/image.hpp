
#ifndef _CORE_IMAGE_HPP

  #define _CORE_IMAGE_HPP

  #include <math.h>

  #include <SDL2/SDL.h>
  #include <SDL2/SDL_image.h>


  class Image {

    private:

      SDL_Surface* surface;
      SDL_Texture* texture;

    public:

      SDL_Rect view;

      int width;
      int height;

      Image() {
        this->surface = NULL;
        this->texture = NULL;
      }

      ~Image() {
        SDL_FreeSurface(this->surface);
        SDL_DestroyTexture(this->texture);
      }

      static Image* load(const char* filename, uint16_t viewX, uint16_t viewY, uint16_t viewW=0, uint16_t viewH=0) {
        Image* img = new Image();

        img->surface = IMG_Load(filename);
        img->view = { viewX, viewY, viewW, viewH };

        return img;
      }

      void render(
        SDL_Renderer* renderer,
        uint32_t dstX,
        uint32_t dstY,
        float dstScaleHorz,
        float dstScaleVert,
        uint32_t srcX,
        uint32_t srcY,
        uint32_t srcWidth,
        uint32_t srcHeight,
        float dstAngle=0.0,
        uint32_t centerX=0,
        uint32_t centerY=0
      ) {

        int imgWidth;
        int imgHeight;

        SDL_Texture* texture = NULL;

        if (this->texture == NULL) {
          texture = SDL_CreateTextureFromSurface(renderer, this->surface);

          SDL_QueryTexture(texture, NULL, NULL, &imgWidth, &imgHeight);

          this->texture = texture;
          this->width = imgWidth;
          this->height = imgHeight;

        } else {
          texture = this->texture;
        }

        SDL_Rect srcRect = {
          (uint16_t)srcX,
          (uint16_t)srcY,
          (uint16_t)srcWidth,
          (uint16_t)srcHeight
        };

        SDL_Point center = {
          (uint16_t)round(centerX * dstScaleHorz),
          (uint16_t)round(centerY * dstScaleVert)
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

        SDL_Rect dstRect = {
          (uint16_t)dstX - center.x,
          (uint16_t)dstY - center.y,
          (uint16_t)round(srcRect.w * dstScaleHorz),
          (uint16_t)round(srcRect.h * dstScaleVert),
        };

        SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, dstAngle, &center, SDL_FLIP_NONE);
      }

  };

#endif
