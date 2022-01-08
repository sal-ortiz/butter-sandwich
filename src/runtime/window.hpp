
#ifndef _WINDOW_HPP

  #define _WINDOW_HPP

  #include <SDL2/SDL.h>

  #include "./image.hpp"


  class Window {

    private:

      SDL_Window* handle;
      SDL_Renderer* renderer;


    public:

      ~Window() {
        SDL_DestroyRenderer(this->renderer);
        SDL_DestroyWindow(this->handle);
      }

      void open(const char* title, uint32_t xPos, uint32_t yPos, uint32_t width,uint32_t height) {
        uint32_t windowFlags = SDL_WINDOW_ALLOW_HIGHDPI;
        uint32_t rendererFlags = SDL_RENDERER_ACCELERATED;

        this->handle = SDL_CreateWindow(title, xPos, yPos, width, height, windowFlags);
        this->renderer = SDL_CreateRenderer(this->handle, -1, rendererFlags);
      }

      void close() {
        SDL_DestroyWindow(this->handle);
      }

      void clear() {
        SDL_RenderClear(this->renderer);
      }

      void render() {
        SDL_RenderPresent(this->renderer);
      }

      SDL_Renderer* getRenderer() {
        return renderer;
      }

  };

#endif
