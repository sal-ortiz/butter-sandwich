
#include "./runtime/event.hpp"



class Application {

  private:

    Event* events;


  public:

    bool isRunning;

    Application() {
      this->isRunning = true;
      this->events = new Event();

      this->events->on("CLOSE", quitCallback);
      this->events->on("QUIT", quitCallback);
    }

    bool evaluate() {
      return Event::poll();
    }

    static void on(const char* id, bool(*callback)()) {
      Event::on(id, callback);
    }

    static bool quitCallback() {
      printf("QUITTING!!!!\n");

      return false;
    }

};
