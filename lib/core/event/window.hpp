
#ifndef _WINDOW_EVENT_HPP

  #define _WINDOW_EVENT_HPP

  #include "./base.hpp"


  struct WindowEventParams: EventParamsBase {
    signed long int horz;
    signed long int vert;

  };


  class WindowEvent: public EventBase {

    private:

      static WindowEventParams parseEventParams(SDL_WindowEvent evt) {
        WindowEventParams params = {
          evt.timestamp,
          evt.windowID,
          NULL,

          evt.data1,
          evt.data2
        };

        return params;
      }


    public:

      static void* parse(SDL_WindowEvent evt) {
        void* retVal = (void*)true;
        WindowEventParams params = WindowEvent::parseEventParams(evt);

        switch (evt.event) {

          case SDL_WINDOWEVENT_CLOSE:
            retVal = handleEvent("WindowEvent.CLOSED", evt, params);
            break;

          case SDL_WINDOWEVENT_MOVED:
            retVal = handleEvent("WindowEvent.MOVED", evt, params);
            break;

          case SDL_WINDOWEVENT_RESIZED:
            retVal = handleEvent("WindowEvent.RESIZED", evt, params);
            break;

        }

        return retVal;
      }

      static void* handleEvent(const char* name, SDL_WindowEvent evt, WindowEventParams params) {
        void* retVal = (void*)true;

        if (_callbacks.has(name)) {
          CallbackRecord callbackRec = _callbacks.get(name);

          void*(*callback)(void*) = callbackRec.method;

          params.data = callbackRec.input;
          retVal = callback((void*)&params);
        }

        return retVal;
      }

  };

#endif




