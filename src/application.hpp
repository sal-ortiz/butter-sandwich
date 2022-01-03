
#include "./runtime/event.hpp"



class Application {

  private:

    Event* events;


  public:

    bool isRunning;
    unsigned long int inp;

    Application() {
      this->inp = 1;

      this->isRunning = false;
      this->events = new Event();

      this->on("CLOSE", quitCallback, &this->inp);
      this->on("QUIT", quitCallback, &this->inp);
    }

    bool evaluate() {
      return Event::poll();
    }

    static void on(const char* id, bool(*callback)(void*), void* inp) {
      Event::on(id, callback, inp);
    }

    static bool quitCallback(void* inp) {
      printf("QUITTING!!!!\t%ld\n", *(unsigned long int*)inp);

      return false;
    }

};
