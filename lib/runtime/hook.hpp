

#ifndef _HOOK_HPP

  #define _HOOK_HPP

  #include "../core/dict.hpp"


  struct HookCallbackRecord {
    void*(*method)(void*, void*);
    void* input;
  };


  Dict<HookCallbackRecord> _hookCallbacks;


  class Hook {

    public:

      static bool hasCallback(const char* id) {
        bool retVal = _hookCallbacks.has(id);

        return retVal;
      }

      static void*(*getCallback(const char* id))(void*, void*) {
        HookCallbackRecord rec = _hookCallbacks.get(id);

        return rec.method;
      }

      static void* getInput(const char* id) {
        HookCallbackRecord rec = _hookCallbacks.get(id);

        return rec.input;
      }

      static void setCallback(const char* id, void*(*callback)(void*, void*), void* inp) {
        HookCallbackRecord rec = { callback, inp };

        _hookCallbacks.set(id, rec);
      }

  };

#endif
