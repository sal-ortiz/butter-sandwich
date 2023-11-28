
#ifndef _APPLICATION_EVENT_HPP

  #define _APPLICATION_EVENT_HPP

  #include <stdint.h>

  #include "./base.hpp"


  struct ApplicationEventParams: EventParamsBase {
    // blank.
  };


  class ApplicationEvent: public EventBase {

    private:

      static ApplicationEventParams* parseEventParams(SDL_QuitEvent evt) {
        ApplicationEventParams* params = new ApplicationEventParams();

        params->timestamp = evt.timestamp;
        params->windowId = (uint32_t)NULL;
        params->data = NULL;

        return params;
      }


    public:

      static void* parse(SDL_QuitEvent evt) {
        ApplicationEventParams* params = ApplicationEvent::parseEventParams(evt);
        void* retVal = ApplicationEvent::handleEvent("SystemEvent.QUIT", evt, params);

        delete params;
        return retVal;
      }

      static void* handleEvent(const char* name, SDL_QuitEvent evt, ApplicationEventParams* params) {
        void* retVal = (void*)true;

        if (_callbacks->has(name)) {
          CallbackRecord* callbackRec = _callbacks->get(name);

          void*(*callback)(void*) = callbackRec->method;

          params->data = callbackRec->input;
          retVal = callback((void*)params);
        }

        return retVal;
      }

  };

#endif
