

#ifndef _RUNTIME_BASE_HPP

  #define _RUNTIME_BASE_HPP

  #include "./hook.hpp"


  class RuntimeBase {

    public:

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
