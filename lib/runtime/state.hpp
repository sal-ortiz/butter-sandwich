
#ifndef _STATE_HPP

  #define _STATE_HPP

  #include <stdint.h>

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

      Dict<void*>* data;


    public:

      State() {
        this->data = new Dict<void*>();
      }

      ~State() {
        List<void*>* dataList = this->data->getValues();
        uint32_t dataListLen = dataList->getLength();

        for (uint32_t idx = 0; idx < dataListLen; idx++) {
          void* entry = dataList->get(idx);

          free(entry);  // free void* vals
        }

        delete dataList;
        delete this->data;
      }

      void* get(const char* key) {
        void* val;
        uint32_t instId = this->getIdentifier();

        char hookId[Hook::ID_LENGTH];
        Hook::generateIdentifier(hookId, "state", instId, key, "get");

        if (this->data->has(key)) {
          val = this->data->get(key);
        }

        HookCallbackParams* inp = new HookCallbackParams();

        inp->target = this;
        inp->newValue = NULL;
        inp->oldValue = val;

        void* outp = this->executeCallback(hookId, (void*)inp);

        HookCallbackParams* retVal = (HookCallbackParams*)outp;

        if (retVal->newValue != NULL) {
          return retVal->newValue;
        }

        return retVal->oldValue;
      }

      void set(const char* key, void* val) {
        void* oldVal;
        uint32_t instId = this->getIdentifier();

        char hookId[Hook::ID_LENGTH];
        Hook::generateIdentifier(hookId, "state", instId, key, "get");

        if (this->data->has(key)) {
          oldVal = this->data->get(key);
        } else {
          oldVal = NULL;
        }

        HookCallbackParams* inp = new HookCallbackParams();

        inp->target = this;
        inp->newValue = val;
        inp->oldValue = oldVal;

        void* outp = this->executeCallback(hookId, (void*)inp);

        HookCallbackParams* retVal = (HookCallbackParams*)outp;

        if (retVal->newValue != NULL) {
          this->data->set(key, retVal->oldValue);
        }

        this->data->set(key, retVal->newValue);

        delete inp;
      }

      void onGet(const char* key, void*(*callback)(void*, void*, void*)) {
        uint32_t instId = this->getIdentifier();

        char hookId[Hook::ID_LENGTH];
        Hook::generateIdentifier(hookId, "state", instId, key, "get");

        this->on(hookId, callback);

        free(hookId);
      }

      void onSet(const char* key, void*(*callback)(void*, void*, void*)) {
        uint32_t instId = this->getIdentifier();

        char hookId[Hook::ID_LENGTH];
        Hook::generateIdentifier(hookId, "state", instId, key, "set");

        this->on(hookId, callback);

        free(hookId);
      }

  };

#endif
