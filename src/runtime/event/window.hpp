
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

    public:

      static void* parse(SDL_WindowEvent evt) {
        void* retVal = (void*)true;

        switch (evt.event) {

          case SDL_WINDOWEVENT_CLOSE:
            retVal = handleWindowClosedEvent(evt);
            break;

          case SDL_WINDOWEVENT_MOVED:
            retVal = handleWindowMovedEvent(evt);
            break;

        }

        return retVal;
      }

      static void* handleWindowClosedEvent(SDL_WindowEvent evt) {
        void* retVal = (void*)true;

        if (_callbacks.has("CLOSED")) {
          CallbackRecord callbackRec = _callbacks.get("CLOSED");

          void*(*callback)(void*) = callbackRec.method;
          WindowEventParams inp = {
            evt.windowID,
            evt.timestamp,
            evt.data1,
            evt.data2,
            callbackRec.input
          };

          retVal = callback((void*)&inp);
        }

        return retVal;
      }

      static void* handleWindowMovedEvent(SDL_WindowEvent evt) {
        void* retVal = (void*)true;

        if (_callbacks.has("MOVED")) {
          CallbackRecord callbackRec = _callbacks.get("MOVED");

          void*(*callback)(void*) = callbackRec.method;
          WindowEventParams inp = {
            evt.windowID,
            evt.timestamp,
            evt.data1,
            evt.data2,
            callbackRec.input
          };

          retVal = callback((void*)&inp);
        }

        return retVal;
      }

  };

#endif




