
#ifndef _EVENT_BASE_HPP

  #define _EVENT_BASE_HPP

  #include <stdint.h>


  struct EventParamsBase {
    uint32_t timestamp;
    uint32_t windowId;
    void* data;
  };

  struct EventCallbackRecord {
    void*(*method)(EventParamsBase*);
    void* input;
  };


  HashMap<EventCallbackRecord*>* _eventCallbacks;


  class EventBase {
    // blank!
  };

#endif
