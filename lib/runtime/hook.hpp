

#ifndef _HOOK_HPP

  #define _HOOK_HPP

  #include <stdint.h>

  #include <core/map/tree_map.hpp>


  template <typename ... Args>
  struct HookCallbackRecord {
    void*(*method)(Args...);
  };


  template <typename ... Args>
  static TreeMap<HookCallbackRecord<Args...>*>* _hookCallbacks;


  class Hook {

    public:

      static const uint8_t ID_LENGTH = 60;

      static void generateIdentifier(char* dest, const char* objType, uint32_t objId, const char* key, const char* action) {
        sprintf(dest, "%.12s-%.20u-%.12s-%.12s", objType, objId, key, action);
      }

      template <typename ... Args>
      static void initialize() {
        _hookCallbacks<> = new TreeMap<HookCallbackRecord<Args...>*>();
      }

      template <typename ... Args>
      static void deinitialize() {
        List<HookCallbackRecord<Args...>*>* cbList = _hookCallbacks<>->getValues();

        uint32_t cbListLen = cbList->getLength();

        for (uint32_t cbIdx = 0; cbIdx < cbListLen; cbIdx++) {
          HookCallbackRecord<Args...>* record = cbList->get(cbIdx);

          delete record;
        }

        delete cbList;
        delete _hookCallbacks<>;
      }

      template <typename ... Args>
      static void setCallback(const char* id, void*(*callback)(Args...)) {
        HookCallbackRecord<Args...>* rec = new HookCallbackRecord<Args...>();

        rec->method = callback;

        _hookCallbacks<>->set(id, (HookCallbackRecord<>*)rec);
      }

      template <typename ... Args>
      static void* executeCallback(const char* id, Args...args) {
        HookCallbackRecord<>* rec = _hookCallbacks<>->get(id);

        if (rec != NULL) {
          void*(*callback)(Args...) = (void*(*)(Args...))rec->method;

          return callback(args...);
        }

        return NULL;
      }

  };

#endif
