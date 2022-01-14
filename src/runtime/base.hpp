

#ifndef _RUNTIME_BASE_HPP

  #define _RUNTIME_BASE_HPP

  #include <time.h>
  #include <math.h>

  #include "./hook.hpp"


  class RuntimeBase {

    private:

      unsigned long int identifier;

      void generateIdentifier() {
        time_t timestamp = time(NULL);
        unsigned long int num;

        srand(timestamp);

        this->identifier = timestamp % rand();
      }


    public:

      RuntimeBase() {
        this->generateIdentifier();
      }

      void on(const char* id, void*(*callback)(void*), void* inp) {
        Hook::setCallback(id, callback, inp);
      }

      static void executeCallback(const char* id, void* inp) {

        if (Hook::hasCallback(id)) {
          void*(*callback)(void*) = Hook::getCallback(id);

          callback(inp);
        }

      }

  };

#endif
