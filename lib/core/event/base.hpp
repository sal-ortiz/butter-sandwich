
#ifndef _EVENT_BASE_HPP

  #define _EVENT_BASE_HPP

  #include <stdint.h>


  struct EventParamsBase {
    uint32_t timestamp;
    uint32_t windowId;
    void* context;
  };

  struct EventCallbackRecord {
    void*(*method)(EventParamsBase*);
    void* context;
  };


  TreeMap<EventCallbackRecord*>* _eventCallbacks;


  class EventBase {
    // blank!
  };

#endif
