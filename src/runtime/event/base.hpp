
#ifndef _EVENT_BASE_HPP

  #define _EVENT_BASE_HPP


  struct CallbackRecord {
    void*(*method)(void*);
    void* input;
  };

  Dict<CallbackRecord> _callbacks;


  class EventBase {


  };











#endif
