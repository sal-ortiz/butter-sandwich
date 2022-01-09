
#ifndef _APPLICATION_HPP

  #define _APPLICATION_HPP

  #include "./event.hpp"


  class Application {


    public:

      bool isActive;

      void start() {
        this->isActive = true;
      }

      void exit() {
        this->isActive = false;
      }

      bool evaluate() {
        return Event::evaluate();
      }

      static void on(const char* id, void*(*callback)(void*), void* inp) {
        Event::on(id, callback, inp);
      }

  };

#endif
