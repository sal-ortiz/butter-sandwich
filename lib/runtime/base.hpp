

#ifndef _RUNTIME_BASE_HPP

  #define _RUNTIME_BASE_HPP

  #include <stdint.h>
  #include <time.h>
  #include <stdlib.h>

  #include "./hook.hpp"
  #include "../tools/identifier.hpp"


  class RuntimeBase {

    private:

      uint32_t identifier;


    public:

      RuntimeBase() {
        this->identifier = IdentifierTools::generate();
      }

      uint32_t getIdentifier() {
        return this->identifier;
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
