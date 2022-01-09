
#ifndef _APPLICATION_HPP

  #define _APPLICATION_HPP

  #include "./event.hpp"


  class Application {

    public:

      bool evaluate() {
        return Event::poll();
      }

      static void on(const char* id, void*(*callback)(void*), void* inp) {
        Event::on(id, callback, inp);
      }

  };

#endif
