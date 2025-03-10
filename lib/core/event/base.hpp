
#ifndef _EVENT_BASE_HPP

  #define _EVENT_BASE_HPP

  #include <stdint.h>


  struct EventCallbackRecord {
    void*(*method)(void*);
    void* input;
  };


  struct EventParamsBase {
    uint32_t timestamp;
    uint32_t windowId;
    void* data;
  };


  HashMap<EventCallbackRecord*>* _eventCallbacks;


  class EventBase {
    // blank!
  };

#endif
