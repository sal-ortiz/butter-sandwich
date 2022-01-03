
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

    static void on(const char* id, bool(*callback)(unsigned long int*), unsigned long int* inp) {
      Event::on(id, callback, inp);
    }

    static bool quitCallback(unsigned long int* inp) {
      printf("QUITTING!!!!\t%ld\n", *inp);

      return false;
    }

};
