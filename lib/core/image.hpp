
#ifndef _IMAGE_HPP

  #define _IMAGE_HPP

  #include <math.h>

  #include <SDL2/SDL.h>
  #include <SDL2/SDL_image.h>

  #include "./renderer.hpp"
  //#include "../tools/identifier.hpp"  // used by selective rendering


  class Image {

    private:

      //unsigned long int identifier;   // used by selective rendering

      SDL_Surface* surface;
      SDL_Texture* texture;

    public:

      SDL_Rect view;

      int width;
      int height;

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
        uint32_t centerY=0
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

        unsigned long int srcHorzPos = srcX == 0 ? this->view.x : srcX;
        unsigned long int srcVertPos = srcY == 0 ? this->view.y : srcY;
        unsigned long int srcHorzSize = srcWidth == 0 ? this->view.w : srcWidth;
        unsigned long int srcVertSize = srcHeight == 0 ? this->view.h : srcHeight;

        unsigned long int centerHorzPos = round(centerX * dstScaleHorz);
        unsigned long int centerVertPos = round(centerY * dstScaleVert);

        unsigned long int destHorzPos = dstX - centerHorzPos;
        unsigned long int destVertPos = dstY - centerVertPos;
        unsigned long int destHorzSize = srcHorzSize * dstScaleHorz;
        unsigned long int destVertSize = srcVertSize * dstScaleVert;

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
          centerVertPos
        );

      }

  };

#endif
