
#ifndef _RUNTIME_STATE_HPP

  #define _RUNTIME_STATE_HPP

  #include <SDL2/SDL.h>

  #include "./base.hpp"
  #include "../core.hpp"


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

        sprintf(hookId, "state.%s.%ld.%s", action, instIdentifier, key);

        return hookId;
      }


    public:

      void* get(const char* key) {
        char* identifier = this->generateHookIdentifier(key, "get");
        void* val;

        if (this->data.has(key)) {
          val = this->data.get(key);
        }

        HookCallbackParams inp = { (void*)this, (void*)NULL, val };
        void* outp = RuntimeBase::executeCallback(identifier, (void*)&inp);

        HookCallbackParams retVal = *(HookCallbackParams*)outp;

        if (retVal.newValue != NULL) {
          return retVal.newValue;
        }

        return retVal.oldValue;
      }

      void set(const char* key, void* val) {
        char* identifier = this->generateHookIdentifier(key, "set");
        void* oldVal;

        if (this->data.has(key)) {
          oldVal = this->data.get(key);
        } else {
          oldVal = NULL;
        }

        HookCallbackParams inp = { (void*)this, val, oldVal };
        void* outp = RuntimeBase::executeCallback(identifier, (void*)&inp);

        HookCallbackParams retVal = *(HookCallbackParams*)outp;

        if (retVal.newValue != NULL) {
          this->data.set(key, retVal.oldValue);
        }

        this->data.set(key, retVal.newValue);
      }

      void onGet(const char* key, void*(*callback)(void*, void*, void*)) {
        char* id = this->generateHookIdentifier(key, "get");

        RuntimeBase::on(id, callback);
      }

      void onSet(const char* key, void*(*callback)(void*, void*, void*)) {
        const char* id = this->generateHookIdentifier(key, "set");

        RuntimeBase::on(id, callback);
      }

  };

#endif
