
#ifndef _WINDOW_EVENT_HPP

  #define _WINDOW_EVENT_HPP

  #include "./base.hpp"


  struct WindowEventParams {

    unsigned long int id;
    unsigned long int timestamp;

    signed long int horz;
    signed long int vert;

    void* user;
  };


  class WindowEvent: public EventBase {

    private:

      static WindowEventParams parseEventParams(SDL_WindowEvent evt) {
        WindowEventParams params = {
          evt.windowID,
          evt.timestamp,
          evt.data1,
          evt.data2,
          NULL
        };

        return params;
      }


    public:

      static void* parse(SDL_WindowEvent evt) {
        void* retVal = (void*)true;
        WindowEventParams params;

        switch (evt.event) {

          case SDL_WINDOWEVENT_CLOSE:
            params = WindowEvent::parseEventParams(evt);

            retVal = handleWindowClosedEvent(evt, params);
            break;

          case SDL_WINDOWEVENT_MOVED:
            params = WindowEvent::parseEventParams(evt);

            retVal = handleWindowMovedEvent(evt, params);
            break;

        }

        return retVal;
      }

      static void* handleWindowClosedEvent(SDL_WindowEvent evt, WindowEventParams params) {
        void* retVal = (void*)true;

        if (_callbacks.has("CLOSED")) {
          CallbackRecord callbackRec = _callbacks.get("CLOSED");

          void*(*callback)(void*) = callbackRec.method;

          params.user = callbackRec.input;
          retVal = callback((void*)&params);
        }

        return retVal;
      }

      static void* handleWindowMovedEvent(SDL_WindowEvent evt, WindowEventParams params) {
        void* retVal = (void*)true;

        if (_callbacks.has("MOVED")) {
          CallbackRecord callbackRec = _callbacks.get("MOVED");

          void*(*callback)(void*) = callbackRec.method;

          params.user = callbackRec.input;
          retVal = callback((void*)&params);
        }

        return retVal;
      }

  };

#endif




