

#ifndef _HOOK_HPP

  #define _HOOK_HPP

  #include <stdint.h>

  #include "../core/map/tree_map.hpp"


  struct HookCallbackRecord {
    void*(*method)(void*, void*, void*);
    void* dataOne;
    void* dataTwo;
  };


  static TreeMap<HookCallbackRecord*>* _hookCallbacks;


  class Hook {

    public:

      static const uint8_t ID_LENGTH = 60;

      static void generateIdentifier(char* dest, const char* objType, uint32_t objId, const char* key, const char* action) {
        sprintf(dest, "%.12s-%.20u-%.12s-%.12s", objType, objId, key, action);
      }

      static void initialize() {
        _hookCallbacks = new TreeMap<HookCallbackRecord*>();
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
        void* callbackRec = _hookCallbacks->get(id);

        return callbackRec != NULL;
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

      static void* executeCallback(const char* id, void* inpOne=NULL, void* inpTwo=NULL, void* inpThree=NULL) {

        if (Hook::hasCallback(id) == true) {
          void*(*callback)(void*, void*, void*) = Hook::getCallback(id);

          if (inpTwo == NULL) {
            inpTwo = Hook::getInputOne(id);
          }

          if (inpThree == NULL) {
            inpThree = Hook::getInputTwo(id);
          }

          return callback(inpOne, inpTwo, inpThree);
        }

        return inpOne;
      }

  };

#endif
