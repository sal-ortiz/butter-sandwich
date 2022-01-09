
#ifndef _APPLICATION_EVENT_HPP

  #define _APPLICATION_EVENT_HPP

  #include "./base.hpp"


  struct ApplicationEventParams {

    unsigned long int timestamp;

    void* user;
  };


  class ApplicationEvent: public EventBase {

    private:

      static ApplicationEventParams parseEventParams(SDL_QuitEvent evt) {
        ApplicationEventParams params = {
          evt.timestamp,
          NULL
        };

        return params;
      }


    public:

      static void* parse(SDL_QuitEvent evt) {
        ApplicationEventParams params = ApplicationEvent::parseEventParams(evt);

        return ApplicationEvent::handleApplicationQuitEvent(evt, params);
      }

      static void* handleApplicationQuitEvent(SDL_QuitEvent evt, ApplicationEventParams params) {
        void* retVal = (void*)true;

        if (_callbacks.has("QUIT")) {
          CallbackRecord callbackRec = _callbacks.get("QUIT");

          void*(*callback)(void*) = callbackRec.method;

          params.user = callbackRec.input;
          retVal = callback((void*)&params);
        }

        return retVal;
      }

  };

#endif
