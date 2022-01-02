
#include "./runtime/event.hpp"



class Application {

  private:

    Event* events;


  public:

    bool isRunning;
    unsigned long int* inp;

    Application() {
      this->inp = (unsigned long int*)1;

      this->isRunning = false;
      this->events = new Event();

      this->events->on("CLOSE", quitCallback, (void*)inp);
      this->events->on("QUIT", quitCallback, (void*)inp);
    }

    bool evaluate() {
      return Event::poll();
    }

    static void on(const char* id, bool(*callback)(void*), void* inp=NULL) {
      Event::on(id, callback, inp);
    }

    static bool quitCallback(void* inp) {;
      printf("QUITTING!!!!\t%ld\n", *(unsigned long int*)inp);
      //printf("QUITTING!!!!\n");

      return false;
    }

};
