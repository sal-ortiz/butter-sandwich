

#ifndef _IMAGE_HPP
  #define _IMAGE_HPP

  #include <assert.h>
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_image.h>


  class Image {

    private:

      SDL_Surface* surface;
      SDL_Rect view;

    public:

      Image() {
        this->surface = NULL;
      }

      ~Image() {
        SDL_FreeSurface(surface);
      }

      void load(const char* filename, uint32_t viewX, uint32_t viewY, uint32_t viewW=NULL, uint32_t viewH=NULL) {
        this->surface = SDL_LoadBMP(filename);
        this->view = { viewX, viewY, viewW, viewH };
      }

      void render(SDL_Renderer* renderer, SDL_Rect dstRect) {
        int imgWidth, imgHeight;

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, this->surface);
        SDL_QueryTexture(texture, NULL, NULL, &imgWidth, &imgHeight);

        SDL_Rect srcRect = {
          this->view.x,
          this->view.y,
          this->view.w ? this->view.w : imgWidth,
          this->view.h ? this->view.h : imgHeight
        };

        dstRect.w = dstRect.w ? dstRect.w : srcRect.w;
        dstRect.h = dstRect.h ? dstRect.h : srcRect.h;

        SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);

        SDL_DestroyTexture(texture);
      }

  };

#endif
