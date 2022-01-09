
#ifndef _APPLICATION_HPP

  #define _APPLICATION_HPP

  #include "./event.hpp"


  class Application {

    public:

      bool isActive;

      Application() {
        Event::on("QUIT", Application::quitCallback, this);
      }

      void start() {
        this->isActive = true;
      }

      void exit() {
        this->isActive = false;
      }

      bool evaluate() {
        return Event::evaluate();
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
