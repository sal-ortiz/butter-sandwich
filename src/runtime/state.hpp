
#ifndef _WINDOW_HPP

  #define _WINDOW_HPP

  #include <SDL2/SDL.h>

  #include "./base.hpp"
  #include "../core/dict.hpp"


  union StateEntry {
    unsigned long int intVal;
    char* strVal;
    void* ptrVal;
  };


  class State: public RuntimeBase {

    private:

      Dict<StateEntry> data;

      const char* generateHookIdentifier(const char* key, const char* action) {
        char* id;
        sprintf(id, "State.%s.%d.%s", action, this->identifier, key);

        return id;
      }


    public:

      unsigned long int get(const char* key) {
        StateEntry entry = data.get(key);

        return entry.intVal;
      }

      char* get(const char* key) {
        StateEntry entry = data.get(key);

        return entry.strVal;
      }

      void* get(const char* key) {
        StateEntry entry = data.get(key);

        return entry.ptrVal;
      }

      void set(const char* key, unsigned long int val) {
        StateEntry entry;
        entry.intVal = val;

        data.set(key, val);
      }

      void set(const char* key, char* val) {
        StateEntry entry;
        entry.strVal = val;

        data.set(key, val);
      }

      void set(const char* key, void* val) {
        StateEntry entry;
        entry.ptrVal = val;

        data.set(key, val);
      }

      void onGet(const char* key, void*(*callback)(void*)) {
        char* id = this->generateHookIdentifier(key, "get");

        RuntimeBase::on(id, callback, (void*)NULL);
      }

      void onSet(const char* key, void*(*callback)(void*)) {
        char* id = this->generateHookIdentifier(key, "set");

        RuntimeBase::on(id, callback, (void*)NULL);
      }

  };

#endif
