

#ifndef _HOOK_HPP

  #define _HOOK_HPP

  #include "../core/dict.hpp"


  struct HookCallbackRecord {
    void*(*method)(void*, void*, void*);
    void* dataOne;
    void* dataTwo;
  };


  Dict<HookCallbackRecord*> _hookCallbacks;


  class Hook {

    public:

      static char* generateIdentifier(const char* objType, unsigned long int objId, const char* key) {
        char* identifier = new char[69];

        sprintf(identifier, "%.24s-%.20lu-%.24s", objType, objId, key);

        return identifier;
      }

      static bool hasCallback(const char* id) {
        bool retVal = _hookCallbacks.has(id);

        return retVal;
      }

      static void*(*getCallback(const char* id))(void*, void*, void*) {
        HookCallbackRecord* rec = _hookCallbacks.get(id);

        return rec->method;
      }

      static void* getInputOne(const char* id) {
        HookCallbackRecord* rec = _hookCallbacks.get(id);

        return rec->dataOne;
      }

      static void* getInputTwo(const char* id) {
        HookCallbackRecord* rec = _hookCallbacks.get(id);

        return rec->dataTwo;
      }

      static void setCallback(const char* id, void*(*callback)(void*, void*, void*), void* dataOne, void* dataTwo) {
        HookCallbackRecord* rec = new HookCallbackRecord();

        rec->method = callback;
        rec->dataOne = dataOne;
        rec->dataTwo = dataTwo;

        _hookCallbacks.set(id, rec);
      }

  };

#endif
