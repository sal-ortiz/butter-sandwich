
#include "./runtime/event.hpp"



class Application {

  private:

    Event* events;


  public:


    Application() {
      this->events = new Event();
    }

    bool evaluate() {
      return Event::poll();
    }

    static void on(const char* id, bool(*callback)(void*), void* inp) {
      Event::on(id, callback, inp);
    }

};
