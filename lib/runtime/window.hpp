
#ifndef _WINDOW_HPP

  #define _WINDOW_HPP

  #include <stdint.h>

  #include <SDL2/SDL.h>

  #include "./base.hpp"
  #include "../core/event.hpp"
  #include "../core/renderer.hpp"


  class Window: public RuntimeBase {

    private:

      SDL_Window* handle;
      Renderer* renderer;


    public:

      Window() {
        Event::on("WindowEvent.CLOSED", Window::closedCallback, this);
        Event::on("WindowEvent.MOVED", Window::movedCallback, this);
        Event::on("WindowEvent.RESIZED", Window::resizedCallback, this);
        Event::on("UserEvent.WINDOWPRESENT", Window::presentCallback, this);
      }

      ~Window() {
        delete this->renderer;

        SDL_DestroyWindow(this->handle);
      }

      void open(const char* title, uint32_t xPos, uint32_t yPos, uint32_t width,uint32_t height) {
        uint32_t windowFlags = SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE /*| SDL_WINDOW_INPUT_GRABBED*/;

        this->handle = SDL_CreateWindow(title, xPos, yPos, width, height, windowFlags);
        this->renderer = new Renderer(this->handle);
      }

      void close() {
        SDL_DestroyWindow(this->handle);
      }

      void clear() {
        this->renderer->clear();
      }

      void render() {
        //Event::pushEvent(PRESENT_WINDOW);

        this->renderer->present();
      }

      Renderer* getRenderer() {
        return this->renderer;
      }

      static void* closedCallback(void* inp) {
        WindowEventParams* params = reinterpret_cast<WindowEventParams*>(inp);
        Window* win = (Window*)params->data;

        void* retVal = Runtime::executeCallback("CLOSED", inp);

        win->close();

        return retVal;
      }

      static void* movedCallback(void* inp) {
        WindowEventParams* params = reinterpret_cast<WindowEventParams*>(inp);
        void* retVal = Runtime::executeCallback("MOVED", inp);

        //printf("MOVED TO %ld, %ld\n", params->horz, params->vert);

        return retVal;
      }

      static void* resizedCallback(void* inp) {
        WindowEventParams* params = reinterpret_cast<WindowEventParams*>(inp);
        void* retVal = Runtime::executeCallback("RESIZED", inp);

        //printf("RESIZED TO %ld, %ld\n", params->horz, params->vert);

        return retVal;
      }

      static void* presentCallback(void* inp) {
        UserEventParams* params = reinterpret_cast<UserEventParams*>(inp);
        void* retVal = Runtime::executeCallback("PRESENT", inp);

        //printf("RENDERING WINDOW\n");

        return retVal;
      }

  };

#endif
