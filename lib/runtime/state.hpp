
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

      static const unsigned char HOOK_ID_LENGTH = 67;

      Dict<void*>* data;

      static void generateHookIdentifier(char* dest, unsigned long int instId, const char* key, const char* action) {

        sprintf(dest, "state-%.24s-%.10ld-%.24s", action, instId, key);
      }


    public:

      State() {
        this->data = new Dict<void*>();
      }

      ~State() {
        delete this->data;
      }

      void* get(const char* key) {
        void* val;

        char hookId[State::HOOK_ID_LENGTH];
        unsigned long int instId = this->getIdentifier();

        State::generateHookIdentifier(hookId, instId, key, "get");

        if (this->data->has(key)) {
          val = this->data->get(key);
        }

        HookCallbackParams* inp = new HookCallbackParams();

        inp->target = this;
        inp->newValue = NULL;
        inp->oldValue = val;

        void* outp = RuntimeBase::executeCallback(hookId, (void*)inp);

        HookCallbackParams* retVal = (HookCallbackParams*)outp;

        if (retVal->newValue != NULL) {
          return retVal->newValue;
        }

        return retVal->oldValue;
      }

      void set(const char* key, void* val) {
        void* oldVal;

        char hookId[State::HOOK_ID_LENGTH];
        unsigned long int instId = this->getIdentifier();

        State::generateHookIdentifier(hookId, instId, key, "get");

        if (this->data->has(key)) {
          oldVal = this->data->get(key);
        } else {
          oldVal = NULL;
        }

        HookCallbackParams* inp = new HookCallbackParams();

        inp->target = this;
        inp->newValue = val;
        inp->oldValue = oldVal;

        void* outp = RuntimeBase::executeCallback(hookId, (void*)inp);

        HookCallbackParams* retVal = (HookCallbackParams*)outp;

        if (retVal->newValue != NULL) {
          this->data->set(key, retVal->oldValue);
        }

        this->data->set(key, retVal->newValue);
      }

      void onGet(const char* key, void*(*callback)(void*, void*, void*)) {
        char hookId[State::HOOK_ID_LENGTH];
        unsigned long int instId = this->getIdentifier();

        State::generateHookIdentifier(hookId, instId, key, "get");

        RuntimeBase::on(hookId, callback);
      }

      void onSet(const char* key, void*(*callback)(void*, void*, void*)) {
        char hookId[State::HOOK_ID_LENGTH];
        unsigned long int instId = this->getIdentifier();

        State::generateHookIdentifier(hookId, instId, key, "set");

        RuntimeBase::on(hookId, callback);
      }

  };

#endif
