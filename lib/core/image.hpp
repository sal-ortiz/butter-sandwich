
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

      void render(SDL_Renderer* renderer, SDL_Rect dstRect, double angle, SDL_Point center) {

        SDL_Rect srcRect = {
          this->view.x,
          this->view.y,
          this->view.w,
          this->view.h
        };

        this->render(renderer, dstRect, srcRect, angle, center);
      }

      void render(SDL_Renderer* renderer, SDL_Rect dstRect, SDL_Rect srcRect, double angle, SDL_Point center) {
        //int imgWidth, imgHeight;

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, this->surface);
        //SDL_QueryTexture(texture, NULL, NULL, &imgWidth, &imgHeight);

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

        SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, angle, &center, SDL_FLIP_NONE);

        SDL_DestroyTexture(texture);
      }

  };


#endif
