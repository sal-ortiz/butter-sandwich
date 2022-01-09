
#ifndef _APPLICATION_EVENT_HPP

  #define _APPLICATION_EVENT_HPP

  #include "./base.hpp"


  class ApplicationEvent: public EventBase {

    public:

      static void* parse(SDL_QuitEvent evt) {
        return ApplicationEvent::handleApplicationQuitEvent(evt);
      }

      static void* handleApplicationQuitEvent(SDL_QuitEvent evt) {
        void* retVal = (void*)true;

        if (_callbacks.has("QUIT")) {
          CallbackRecord callbackRec = _callbacks.get("QUIT");

          void*(*callback)(void*) = callbackRec.method;
          void* inp = callbackRec.input;

          retVal = callback(inp);
        }

        return retVal;
      }

  };

#endif
