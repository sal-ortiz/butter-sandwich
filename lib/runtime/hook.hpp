

#ifndef _RUNTIME_HOOK_HPP

  #define _RUNTIME_HOOK_HPP

  #include "../core.hpp"


  struct HookCallbackRecord {
    void*(*method)(void*, void*, void*);
    void* dataOne;
    void* dataTwo;
  };

  Dict<HookCallbackRecord> _hookCallbacks;

  class Hook {

    public:

      static char* generateIdentifier(unsigned long int objId, const char* key) {
        char* identifier = new char[64];

        sprintf(identifier, "hook-%ld-%s", objId, key);

        return identifier;
      }

      static bool hasCallback(const char* id) {
        bool retVal = _hookCallbacks.has(id);

        return retVal;
      }

      static void*(*getCallback(const char* id))(void*, void*, void*) {
        HookCallbackRecord rec = _hookCallbacks.get(id);

        return rec.method;
      }

      static void* getInputOne(const char* id) {
        HookCallbackRecord rec = _hookCallbacks.get(id);

        return rec.dataOne;
      }

      static void* getInputTwo(const char* id) {
        HookCallbackRecord rec = _hookCallbacks.get(id);

        return rec.dataTwo;
      }

      static void setCallback(const char* id, void*(*callback)(void*, void*, void*), void* dataOne, void* dataTwo) {
        HookCallbackRecord rec = { callback, dataOne, dataTwo };

        _hookCallbacks.set(id, rec);
      }

  };

#endif
