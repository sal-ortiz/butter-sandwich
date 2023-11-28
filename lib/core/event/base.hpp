
#ifndef _EVENT_BASE_HPP

  #define _EVENT_BASE_HPP

  #include <stdint.h>


  struct CallbackRecord {
    void*(*method)(void*);
    void* input;
  };


  struct EventParamsBase {
    uint32_t timestamp;
    uint32_t windowId;
    void* data;
  };


  Dict<CallbackRecord*>* _callbacks;


  class EventBase {
    // blank!
  };

#endif
