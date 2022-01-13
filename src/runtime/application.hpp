
#ifndef _APPLICATION_HPP

  #define _APPLICATION_HPP

  #include "./base.hpp"
  #include "../core/event.hpp"


  class Application: public RuntimeBase {

    public:

      bool isActive;

      Application() {
        Event::on("SystemEvent.QUIT", Application::quitCallback, this);
      }

      void start() {
        this->isActive = true;
      }

      void exit() {
        this->isActive = false;
      }

      void on(const char* id, void*(*callback)(void*), void* inp) {
        Hook::setCallback(id, callback, inp);
      }

      static void* quitCallback(void* inp) {
        WindowEventParams* params = reinterpret_cast<WindowEventParams*>(inp);
        Application* app = (Application*)params->data;

        RuntimeBase::executeCallback("QUIT", inp);

        app->exit();

        return (void*)NULL;
      }

  };

#endif