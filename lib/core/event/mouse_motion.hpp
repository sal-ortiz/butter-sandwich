

#ifndef _EVENT_MOUSE_MOTION_HPP

  #define _EVENT_MOUSE_MOTION_HPP

  #include "./base.hpp"


  struct MouseMotionEventParams: EventParamsBase {
    unsigned long int mouseId;
    unsigned long int state;

    signed long int absoluteHorzPos;
    signed long int absoluteVertPos;

    signed long int relativeHorzPos;
    signed long int relativeVertPos;
  };


  class MouseMotionEvent: public EventBase {

    private:

      static MouseMotionEventParams parseEventParams(SDL_MouseMotionEvent evt) {
        MouseMotionEventParams params = {
          evt.timestamp,
          evt.windowID,
          NULL,

          evt.which,
          evt.state,

          evt.x,
          evt.y,
          evt.xrel,
          evt.yrel
        };

        return params;
      }


    public:

      static void* parse(SDL_MouseMotionEvent evt) {
        MouseMotionEventParams params = MouseMotionEvent::parseEventParams(evt);

        return MouseMotionEvent::handleEvent("SystemEvent.MOUSEMOTION", evt, params);
      }

      static void* handleEvent(const char* name, SDL_MouseMotionEvent, MouseMotionEventParams params) {
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
