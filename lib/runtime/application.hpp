
#ifndef _APPLICATION_HPP

  #define _APPLICATION_HPP

  #include "./base.hpp"
  #include "../core/event.hpp"


  class Application: public RuntimeBase {

    public:

      bool isActive;

      Application() {
        Event::on("SystemEvent.QUIT", Application::quitCallback, this);
        Event::on("SystemEvent.KEYBOARD", Application::keyboardCallback, this);
        Event::on("SystemEvent.MOUSEMOTION", Application::mouseMotionCallback, this);
        Event::on("SystemEvent.MOUSEBUTTON", Application::mouseButtonCallback, this);
      }

      void start() {
        this->isActive = true;
      }

      void exit() {
        this->isActive = false;
      }

      static void* quitCallback(void* inp) {
        ApplicationEventParams* params = reinterpret_cast<ApplicationEventParams*>(inp);
        Application* app = (Application*)params->data;

        void* retVal = RuntimeBase::executeCallback("QUIT", inp);

        app->exit();

        return retVal;
      }

      static void* keyboardCallback(void* inp) {
        //KeyboardEventParams* params = reinterpret_cast<KeyboardEventParams*>(inp);

        void* retVal = RuntimeBase::executeCallback("KEYBOARD", inp);

        return retVal;
      }

      static void* mouseMotionCallback(void* inp) {
        //MouseMotionEventParams* params = reinterpret_cast<MouseMotionEventParams*>(inp);

        void* retVal = RuntimeBase::executeCallback("MOUSEMOTION", inp);

        return retVal;
      }

      static void* mouseButtonCallback(void* inp) {
        //MouseButtonEventParams* params = reinterpret_cast<MouseButtonEventParams*>(inp);

        void* retVal = RuntimeBase::executeCallback("MOUSEBUTTON", inp);

        return retVal;
      }

  };

#endif
