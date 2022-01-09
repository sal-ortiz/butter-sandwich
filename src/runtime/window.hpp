
#ifndef _WINDOW_HPP

  #define _WINDOW_HPP

  #include <SDL2/SDL.h>

  #include "./image.hpp"
  #include "./event.hpp"


  class Window {

    private:

      SDL_Window* handle;
      SDL_Renderer* renderer;


    public:

      Window() {
        Event::on("CLOSED", Window::closedCallback, this);
        Event::on("MOVED", Window::movedCallback, this);
        Event::on("RESIZED", Window::resizedCallback, this);
      }

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

      static void* closedCallback(void* inp) {
        WindowEventParams* params = reinterpret_cast<WindowEventParams*>(inp);
        Window* win = (Window*)params->user;

        printf("CLOSING!!!!\t\n");
        win->close();

        return (void*)NULL;
      }

      static void* movedCallback(void* inp) {
        WindowEventParams* params = reinterpret_cast<WindowEventParams*>(inp);

        printf("MOVED TO %ld, %ld\n", params->horz, params->vert);

        return (void*)NULL;
      }

      static void* resizedCallback(void* inp) {
        WindowEventParams* params = reinterpret_cast<WindowEventParams*>(inp);

        printf("RESIZED TO %ld, %ld\n", params->horz, params->vert);

        return (void*)NULL;
      }

  };

#endif
