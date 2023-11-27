

#ifndef _MOUSE_MOTION_EVENT_HPP

  #define _MOUSE_MOTION_EVENT_HPP

  #include <stdint.h>

  #include "./base.hpp"


  struct MouseMotionEventParams: EventParamsBase {
    uint32_t mouseId;
    uint32_t state;

    int32_t absoluteHorzPos;
    int32_t absoluteVertPos;

    int32_t relativeHorzPos;
    int32_t relativeVertPos;
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

        if (_callbacks->has(name)) {
          CallbackRecord* callbackRec = _callbacks->get(name);

          void*(*callback)(void*) = callbackRec->method;

          params.data = callbackRec->input;
          retVal = callback((void*)&params);
        }

        return retVal;
      }

  };

#endif
