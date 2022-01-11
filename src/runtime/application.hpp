
#ifndef _APPLICATION_HPP

  #define _APPLICATION_HPP

  #include "../core/event.hpp"


  class Application: public Event {

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

      static void* quitCallback(void* inp) {
        WindowEventParams* params = reinterpret_cast<WindowEventParams*>(inp);
        Application* app = (Application*)params->data;

        printf("QUITTING!!!!\t\n");
        app->exit();

        return (void*)NULL;
      }

  };

#endif
