
#ifndef _STATE_HPP

  #define _STATE_HPP

  #include <stdint.h>

  #include <SDL2/SDL.h>

  #include <runtime/base.hpp>
  #include <core/map/hash_map.hpp>


  //struct HookCallbackParams {
  //  void* target;
  //  void* newValue;
  //  void* oldValue;
  //};


  class State: public RuntimeBase {

    private:

      HashMap<void*>* data;


    public:

      State() {
        this->data = new HashMap<void*>();
      }

      ~State() {
        //// TODO: It's possible that not all of the value stored here
        ////       are pointers. If this is the case, then trying to
        ////       delete them here might break. Perhaps these values
        ////       should be deleted by the lib that created them.
        //List<void*>* dataList = this->data->getValues();
        //uint32_t dataListLen = dataList->getLength();
        //
        //for (uint32_t idx = 0; idx < dataListLen; idx++) {
        //  void* entry = dataList->get(idx);
        //
        //  delete entry;
        //  //free(entry);  // free void* vals
        //}
        //
        //delete dataList;
        delete this->data;
      }

      void* get(const char* key) {
        //  // TODO: REFACTOR GETTERS!!!!!!!?
        void* val;
        //uint32_t instId = this->getIdentifier();
        //
        //char hookId[Hook::ID_LENGTH];
        //Hook::generateIdentifier(hookId, "state", instId, key, "get");
        //
        val = this->data->get(key);
        //
        //HookCallbackParams* inp = new HookCallbackParams();
        //
        //inp->target = this;
        //inp->newValue = NULL;
        //inp->oldValue = val;
        //
        //void* outp = Hook::executeCallback(hookId, (void*)inp);
        //
        //HookCallbackParams* retVal = (HookCallbackParams*)outp;
        //
        //if (retVal->newValue != NULL) {
        //  return retVal->newValue;
        //}

        //return retVal->oldValue;
        return val;
      }

      void set(const char* key, void* val) {
        //  // TODO: REFACTOR SETTERS!!!!!!!?
        //void* oldVal;
        //uint32_t instId = this->getIdentifier();

        //char hookId[Hook::ID_LENGTH];
        //Hook::generateIdentifier(hookId, "state", instId, key, "get");
        //
        //oldVal = this->data->get(key);
        //
        //HookCallbackParams* inp = new HookCallbackParams();
        //
        //inp->target = this;
        //inp->newValue = val;
        //inp->oldValue = oldVal;
        //
        //void* outp = Hook::executeCallback(hookId, (void*)inp);
        //
        //HookCallbackParams* retVal = (HookCallbackParams*)outp;
        //
        //if (retVal->newValue != NULL) {
        //  this->data->set(key, retVal->oldValue);
        //}
        //
        //this->data->set(key, retVal->newValue);

        this->data->set(key, val);

        //delete inp;
      }

      //void onGet(const char* key, void*(*callback)(void*, void*, void*)) {
      //  // TODO: REFACTOR GETTERS!!!!!!!?
      //  uint32_t instId = this->getIdentifier();
      //
      //  char hookId[Hook::ID_LENGTH];
      //  Hook::generateIdentifier(hookId, "state", instId, key, "get");
      //
      //  this->on(hookId, callback);
      //
      //  free(hookId);
      //}

      //void onSet(const char* key, void*(*callback)(void*, void*, void*)) {
      //  // TODO: REFACTOR SETTERS!!!!!!!?
      //  uint32_t instId = this->getIdentifier();
      //
      //  char hookId[Hook::ID_LENGTH];
      //  Hook::generateIdentifier(hookId, "state", instId, key, "set");
      //
      //  this->on(hookId, callback);
      //
      //  free(hookId);
      //}

  };

#endif
