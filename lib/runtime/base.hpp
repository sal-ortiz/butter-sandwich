

#ifndef _RUNTIME_BASE_HPP

  #define _RUNTIME_BASE_HPP

  #include <stdint.h>
  #include <time.h>
  #include <stdlib.h>
  #include <string.h>

  #include "./hook.hpp"
  #include "../tools/identifier.hpp"


  class RuntimeBase {

    private:

      uint32_t intIdentifier;
      char strIdentifier[10];


    public:

      RuntimeBase() {
        this->intIdentifier = IdentifierTools::generate();

        sprintf(this->strIdentifier, "%u", this->intIdentifier);
      }

      uint32_t getIdentifier() {
        return this->intIdentifier;
      }

      char* getIdentifierString() {
        return this->strIdentifier;
      }

      void on(const char* id, void*(*callback)(void*, void*, void*), void* dataOne=NULL, void* dataTwo=NULL) {
        Hook::setCallback(id, callback, dataOne, dataTwo);
      }

      void* executeCallback(const char* id, void* inpOne=NULL, void* inpTwo=NULL, void* inpThree=NULL) {

        if (Hook::hasCallback(id) == true) {
          void* retVal = Hook::executeCallback(id, inpOne, inpTwo, inpThree);

          return retVal;
        }

        return inpOne;
      }

  };

#endif
