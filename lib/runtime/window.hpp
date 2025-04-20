
#ifndef _WINDOW_HPP

  #define _WINDOW_HPP

  #include <stdint.h>

  #include <SDL2/SDL.h>

  #include <runtime/base.hpp>
  #include <core/event.hpp>
  #include <core/renderer.hpp>
  #include <core/thread.hpp>


  class Window: public RuntimeBase {

    private:

      SDL_Window* handle;
      Renderer* renderer;

      uint32_t id;

      //Thread* renderThread;


    public:

      Window() {
        Event::on("WindowEvent.CLOSED", (void* (*)(EventParamsBase*))Window::closedCallback, this);
        Event::on("WindowEvent.MOVED", (void* (*)(EventParamsBase*))Window::movedCallback, this);
        Event::on("WindowEvent.RESIZED", (void* (*)(EventParamsBase*))Window::resizedCallback, this);
        Event::on("UserEvent.WINDOWPRESENT", (void* (*)(EventParamsBase*))Window::presentCallback, this);

        //this->renderThread = new Thread();
      }

      ~Window() {
        delete this->renderer;
        //delete this->renderThread;

        SDL_DestroyWindow(this->handle);
      }

      void open(const char* title, uint32_t xPos, uint32_t yPos, uint32_t width,uint32_t height) {
        uint32_t windowFlags = SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE /*| SDL_WINDOW_INPUT_GRABBED*/;

        this->handle = SDL_CreateWindow(title, xPos, yPos, width, height, windowFlags);
        this->renderer = new Renderer(this->handle);
        this->id = SDL_GetWindowID(this->handle);

        //this->renderThread->execute(Window::renderThreadFunc, this->renderer);
      }

      void close() {
        SDL_DestroyWindow(this->handle);
      }

      void clear() {
        this->renderer->clear();
      }

      void render() {
        //Event::pushEvent(PRESENT_WINDOW);

        //this->renderThread->trigger();
        //this->renderThread->wait();

        //this->renderThread->execute(Window::renderThreadFunc, this->renderer);

        this->renderer->present();
      }

      Renderer* getRenderer() {
        return this->renderer;
      }

      static void* closedCallback(WindowEventParams* params) {
        Window* win = (Window*)params->data;

        uint32_t horzPos = params->horz;
        uint32_t vertPos = params->vert;

        Hook::executeCallback("CLOSED", win, horzPos, vertPos);

        win->close();

        return NULL;
      }

      static void* movedCallback(WindowEventParams* params) {
        Window* win = (Window*)params->data;

        uint32_t horzPos = params->horz;
        uint32_t vertPos = params->vert;

        Hook::executeCallback("MOVED", win, horzPos, vertPos);

        //printf("MOVED TO (%ld, %ld)\n", params->horz, params->vert);

        return NULL;
      }

      static void* resizedCallback(WindowEventParams* params) {
        Window* win = (Window*)params->data;

        uint32_t width = params->horz;
        uint32_t height = params->vert;

        Hook::executeCallback("RESIZED", win, width, height);

        //printf("RESIZED TO (%ld, %ld)\n", params->horz, params->vert);

        return NULL;
      }

      static void* presentCallback(UserEventParams* params) {
        Window* win = (Window*)params->data;

        Hook::executeCallback("PRESENT", win);

        //printf("RENDERING WINDOW\n");

        return NULL;
      }

      //static void* renderThreadFunc(void* inpOne, void* inpTwo, void* inpThree) {
      //  Renderer* renderer = reinterpret_cast<Renderer*>(inpOne);
      //
      //  renderer->present();
      //
      //  return NULL;
      //}

  };

#endif
