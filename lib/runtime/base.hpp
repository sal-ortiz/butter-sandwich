

#ifndef _RUNTIME_BASE_HPP

  #define _RUNTIME_BASE_HPP

  #include <stdint.h>
  #include <time.h>
  #include <stdlib.h>
  #include <string.h>

  #include <core/list/linked_list.hpp>
  #include <runtime/hook.hpp>
  #include <tools/identifier.hpp>


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

      template <typename ... Args>
      void on(const char* id, void*(*callback)(LinkedList<void*>*), Args...args) {
        Hook::setCallback(id, callback, args...);
      }

  };

#endif
