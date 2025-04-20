

#ifndef _HOOK_HPP

  #define _HOOK_HPP

  #include <stdint.h>

  #include <core/map/tree_map.hpp>


  struct HookCallbackRecord {
    void*(*method)(LinkedList<void*>*);

    LinkedList<void*>* arguments;
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

      template <typename ... Args>
      static void setCallback(const char* id, void*(*callback)(LinkedList<void*>*), Args...args) {
        LinkedList<void*>* argsList = new LinkedList<void*>();

        (argsList->push(args), ...);

        HookCallbackRecord* rec = new HookCallbackRecord();

        rec->method = callback;
        rec->arguments = argsList;

        _hookCallbacks->set(id, rec);
      }

      template <typename ... Args>
      static void* executeCallback(const char* id, Args...args) {
        HookCallbackRecord* rec = _hookCallbacks->get(id);

        if (rec != NULL) {
          void*(*callback)(LinkedList<void*>*) = rec->method;
          LinkedList<void*>* recArgsList = rec->arguments;
          LinkedList<void*>* argsList = new LinkedList<void*>();

          (argsList->push((void*)(uintptr_t)args), ...);

          argsList->concat(recArgsList);  // prioritize this function's args
          //recArgsList->concat(argsList);    // prioritize our callback record's args

          return callback(argsList);    // prioritize this function's args
          //return callback(recArgsList);   // prioritize our callback record's args
        }

        return (void*)NULL;
      }

  };

#endif
