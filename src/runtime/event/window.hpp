
#ifndef _WINDOW_EVENT_HPP

  #define _WINDOW_EVENT_HPP

  #include "./base.hpp"


  class WindowEvent: public EventBase {

    public:

      static void* parse(SDL_WindowEvent evt) {
        void* retVal = (void*)true;

        switch (evt.event) {

          case SDL_WINDOWEVENT_CLOSE:
            retVal = handleWindowClose(evt);

            break;

        }

        return retVal;
      }

      static void* handleWindowClose(SDL_WindowEvent evt) {
        void* retVal = (void*)true;

        if (_callbacks.has("CLOSE")) {
          CallbackRecord callbackRec = _callbacks.get("CLOSE");

          void*(*callback)(void*) = callbackRec.method;
          void* inp = callbackRec.input;

          retVal = callback(inp);
        }

        return retVal;
      }

  };

#endif




