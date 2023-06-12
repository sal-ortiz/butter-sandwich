

#ifndef _RUNTIME_BASE_HPP

  #define _RUNTIME_BASE_HPP

  #include <time.h>
  #include <stdlib.h>

  #include "./hook.hpp"


  class RuntimeBase {

    protected:

      unsigned long int identifier;

      unsigned long int generateIdentifier() {
        time_t timestamp = time(NULL);

        srand(timestamp * rand());

        return timestamp % (rand() * rand() * rand());
      }


    public:

      RuntimeBase() {
        this->identifier = this->generateIdentifier();
      }

      unsigned long int getIdentifier() {
        return this->identifier;
      }

      void on(const char* id, void*(*callback)(void*, void*, void*), void* dataOne=NULL, void* dataTwo=NULL) {
        Hook::setCallback(id, callback, dataOne, dataTwo);
      }

      static void* executeCallback(const char* id, void* inp) {

        if (Hook::hasCallback(id) == true) {
          void*(*callback)(void*, void*, void*) = Hook::getCallback(id);
          void* dataOne = Hook::getInputOne(id);
          void* dataTwo = Hook::getInputTwo(id);

          return callback(inp, dataOne, dataTwo);
        }

        return inp;
      }

  };

#endif
