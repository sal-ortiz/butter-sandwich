
#ifndef _APPLICATION_HPP

  #define _APPLICATION_HPP

  #include <SDL2/SDL.h>

  #include <runtime/base.hpp>
  #include <core/event.hpp>


  class Application: public RuntimeBase {

    public:

      bool isActive;

      Application() {
        Event::on("SystemEvent.QUIT", (void* (*)(EventParamsBase*))Application::quitCallback, this);
        Event::on("SystemEvent.KEYBOARD", (void* (*)(EventParamsBase*))Application::keyboardCallback, this);
        Event::on("SystemEvent.MOUSEMOTION", (void* (*)(EventParamsBase*))Application::mouseMotionCallback, this);
        Event::on("SystemEvent.MOUSEBUTTON", (void* (*)(EventParamsBase*))Application::mouseButtonCallback, this);
      }

      ~Application() {
        this->exit();

        SDL_Quit();
      }

      void start() {
        this->isActive = true;
      }

      void exit() {
        this->isActive = false;
      }

      static void* quitCallback(ApplicationEventParams* params) {
        Application* app = (Application*)params->data;

        Hook::executeCallback("QUIT", app);

        app->exit();

        return NULL;
      }

      static void* keyboardCallback(KeyboardEventParams* params) {
        Application* app = (Application*)params->data;

        uint32_t scanCode = params->scanCode;
        bool isPressed = false;

        if (params->state == SDL_PRESSED) {
          isPressed = true;
        }

        KeyboardInput::setState(scanCode, isPressed);

        Hook::executeCallback("KEYBOARD", app, scanCode, isPressed);

        return NULL;
      }

      static void* mouseMotionCallback(MouseMotionEventParams* params) {
        Application* app = (Application*)params->data;

        uint32_t horzPos = params->horzPos;
        uint32_t vertPos = params->vertPos;

        uint32_t horzOffset = params->horzOffset;
        uint32_t vertOffset = params->vertOffset;

        Hook::executeCallback("MOUSEMOTION", app, horzPos, vertPos/*, horzOffset*//*, vertOffset*/);

        //printf("MOUSE AT (%ld, %ld)\n", horzPos, vertPos);

        return NULL;
      }

      static void* mouseButtonCallback(MouseButtonEventParams* params) {
        Application* app = (Application*)params->data;

        uint32_t state = params->state;
        uint32_t button = params->button;
        uint32_t numClicks = params->numClicks;


        Hook::executeCallback("MOUSEBUTTON", button, state, numClicks);

        //printf("MOUSE BUTTON %d %s\n", button, state ? "down" : "up");

        return NULL;
      }

  };

#endif
