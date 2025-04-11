
#ifndef _IMAGE_HPP

  #define _IMAGE_HPP

  #include <math.h>
  #include <stdint.h>

  #include <SDL2/SDL.h>
  #include <SDL2/SDL_image.h>

  #include <core/renderer.hpp>
  //#include <../tools/identifier.hpp>  // used by selective rendering


  class Image {

    private:

      //uint32_t identifier;   // used by selective rendering

      SDL_Surface* surface;
      SDL_Texture* texture;

    public:

      SDL_Rect view;

      uint16_t width;
      uint16_t height;

      Image() {
        //this->identifier = IdentifierTools::generate(); // used by selective rendering

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

        if (viewW == 0) {
          img->width = img->surface->w;
        } else {
          img->width = viewW;
        }

        if (viewH == 0) {
          img->height = img->surface->h;
        } else {
          img->height = viewH;
        }

        return img;
      }

      void render(
        Renderer* renderer,
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
        uint32_t centerY=0,
        uint8_t red=255,
        uint8_t green=255,
        uint8_t blue=255,
        uint8_t alpha=255
      ) {

        //int imgWidth;   // unused
        //int imgHeight;  // unused

        SDL_Texture* texture = NULL;

        if (this->texture == NULL) {
          texture = SDL_CreateTextureFromSurface(renderer->getRenderer(), this->surface);

          //SDL_QueryTexture(texture, NULL, NULL, &imgWidth, &imgHeight);   // unused

          this->texture = texture;

        } else {
          texture = this->texture;
        }

        uint32_t srcHorzPos = srcX == 0 ? this->view.x : srcX;
        uint32_t srcVertPos = srcY == 0 ? this->view.y : srcY;
        uint32_t srcHorzSize = srcWidth == 0 ? this->view.w : srcWidth;
        uint32_t srcVertSize = srcHeight == 0 ? this->view.h : srcHeight;

        uint32_t centerHorzPos = round(centerX * dstScaleHorz);
        uint32_t centerVertPos = round(centerY * dstScaleVert);

        uint32_t destHorzPos = dstX - centerHorzPos;
        uint32_t destVertPos = dstY - centerVertPos;
        uint32_t destHorzSize = srcHorzSize * dstScaleHorz;
        uint32_t destVertSize = srcVertSize * dstScaleVert;

        renderer->render(
          //this->identifier, // used by selective rendering
          texture,
          destHorzPos,
          destVertPos,
          destHorzSize,
          destVertSize,
          srcHorzPos,
          srcVertPos,
          srcHorzSize,
          srcVertSize,
          dstAngle,
          centerHorzPos,
          centerVertPos,
          red,
          green,
          blue,
          alpha
        );

      }

  };

#endif
