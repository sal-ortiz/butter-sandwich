
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




