

#ifndef _RUNTIME_BASE_HPP

  #define _RUNTIME_BASE_HPP

  #include <time.h>
  #include <stdlib.h>

  #include "./hook.hpp"


  unsigned long int MAGIC_NUMBER = 1;


  class RuntimeBase {

    private:

      unsigned long int identifier;

      unsigned long int generateIdentifier() {
        unsigned long int timestamp = SDL_GetTicks();

        MAGIC_NUMBER = (MAGIC_NUMBER * rand()) % 0xffffffff;

        return MAGIC_NUMBER;
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

      static void* executeCallback(const char* id, void* inpOne = NULL, void* inpTwo = NULL, void* inpThree = NULL) {

        if (Hook::hasCallback(id) == true) {
          void*(*callback)(void*, void*, void*) = Hook::getCallback(id);

          if (inpTwo == NULL) {
            inpTwo = Hook::getInputOne(id);
          }

          if (inpThree == NULL) {
            inpThree = Hook::getInputTwo(id);
          }

          return callback(inpOne, inpTwo, inpThree);
        }

        return inpOne;
      }

  };

#endif
