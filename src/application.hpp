
#include "./runtime/event.hpp"



class Application {

  private:

    Event* events;


  public:

    bool isRunning;

    Application() {
      this->isRunning = false;
      this->events = new Event();
    }

    bool evaluate() {
      return Event::poll();
    }

    static void on(const char* id, bool(*callback)(void*), void* inp) {
      Event::on(id, callback, inp);
    }

};
