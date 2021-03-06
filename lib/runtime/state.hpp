
#ifndef _STATE_HPP

  #define _STATE_HPP

  #include <SDL2/SDL.h>

  #include "./base.hpp"
  #include "../core/dict.hpp"


  struct HookCallbackParams {
    void* target;
    void* newValue;
    void* oldValue;
  };


  class State: public RuntimeBase {

    private:

      Dict<void*> data;

      char* generateHookIdentifier(const char* key, const char* action) {
        char* hookId = new char[64];
        unsigned long int instIdentifier = this->getIdentifier();

        sprintf(hookId, "State.%s.%ld.%s", action, instIdentifier, key);

        return hookId;
      }


    public:

      void* get(const char* key) {
        char* identifier = this->generateHookIdentifier(key, "get");
        void* val = (void*)55;


        if (this->data.has(key)) {
          val = this->data.get(key);
        }

        HookCallbackParams params = { (void*)this, (void*)NULL, val };

        val = RuntimeBase::executeCallback(identifier, (void*)&params);

        return val;
      }

      void set(const char* key, void* val) {
        char* identifier = this->generateHookIdentifier(key, "set");
        void* oldVal;

        if (this->data.has(key)) {
          oldVal = this->data.get(key);
        } else {
          oldVal = NULL;
        }

        HookCallbackParams params = { (void*)this, val, oldVal };

        val = RuntimeBase::executeCallback(identifier, (void*)&params);

        this->data.set(key, val);
      }

      void onGet(const char* key, void*(*callback)(void*, void*), void* inp) {
        char* id = this->generateHookIdentifier(key, "get");

        RuntimeBase::on(id, callback, (void*)NULL);
      }

      void onSet(const char* key, void*(*callback)(void*, void*), void* inp) {
        const char* id = this->generateHookIdentifier(key, "set");

        RuntimeBase::on(id, callback, (void*)NULL);
      }

  };

#endif
