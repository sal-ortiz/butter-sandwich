

#ifndef _HOOK_HPP

  #define _HOOK_HPP

  #include <stdint.h>

  #include "../core/dict.hpp"


  struct HookCallbackRecord {
    void*(*method)(void*, void*, void*);
    void* dataOne;
    void* dataTwo;
  };


  Dict<HookCallbackRecord*>* _hookCallbacks;


  class Hook {

    public:

      static const uint8_t ID_LENGTH = 60;

      static void generateIdentifier(char* dest, const char* objType, uint32_t objId, const char* key, const char* action) {
        sprintf(dest, "%.12s-%.20u-%.12s-%.12s", objType, objId, key, action);
      }

      static void initialize() {
        _hookCallbacks = new Dict<HookCallbackRecord*>();
      }

      static void deinitialize() {
        List<HookCallbackRecord*>* cbList = _hookCallbacks->getValues();

        uint32_t cbListLen = cbList->getLength();

        for (uint32_t cbIdx = 0; cbIdx < cbListLen; cbIdx++) {
          HookCallbackRecord* record = cbList->get(cbIdx);

          delete record;
        }

        delete cbList;
        delete _hookCallbacks;
      }

      static bool hasCallback(const char* id) {
        bool retVal = _hookCallbacks->has(id);

        return retVal;
      }

      static void*(*getCallback(const char* id))(void*, void*, void*) {
        HookCallbackRecord* rec = _hookCallbacks->get(id);

        return rec->method;
      }

      static void* getInputOne(const char* id) {
        HookCallbackRecord* rec = _hookCallbacks->get(id);

        return rec->dataOne;
      }

      static void* getInputTwo(const char* id) {
        HookCallbackRecord* rec = _hookCallbacks->get(id);

        return rec->dataTwo;
      }

      static void setCallback(const char* id, void*(*callback)(void*, void*, void*), void* dataOne, void* dataTwo) {
        HookCallbackRecord* rec = new HookCallbackRecord();

        rec->method = callback;
        rec->dataOne = dataOne;
        rec->dataTwo = dataTwo;

        _hookCallbacks->set(id, rec);
      }

  };

#endif
