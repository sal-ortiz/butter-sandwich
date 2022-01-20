
#ifndef _EVENT_BASE_HPP

  #define _EVENT_BASE_HPP


  struct CallbackRecord {
    void*(*method)(void*);
    void* input;
  };

  struct EventParamsBase {
    unsigned long int timestamp;
    unsigned long int windowID;
    void* data;
  };


  Dict<CallbackRecord> _callbacks;


  class EventBase {
    // blank!
  };

#endif
