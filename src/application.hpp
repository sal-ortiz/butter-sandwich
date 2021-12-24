
#include "./runtime/event.hpp"



class Application {

  private:

    Event* events;


  public:

    bool isRunning;

    Application() {
      bool* inp = (bool*)false;

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
      printf("QUITTING!!!!\t%d\n", (bool)(bool*)inp);
      //printf("QUITTING!!!!\n");

      return false;
    }

};
