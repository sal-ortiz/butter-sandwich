

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

      static MouseMotionEventParams* parseEventParams(SDL_MouseMotionEvent evt) {
        MouseMotionEventParams* params = new MouseMotionEventParams();

        params->timestamp = evt.timestamp;
        params->windowId = evt.windowID;
        params->data = NULL;

        params->mouseId = evt.which;
        params->state = evt.state;

        params->absoluteHorzPos = evt.x;
        params->absoluteVertPos = evt.y;
        params->relativeHorzPos = evt.xrel;
        params->relativeVertPos = evt.yrel;

        return params;
      }


    public:

      static void* parse(SDL_MouseMotionEvent evt) {
        MouseMotionEventParams* params = MouseMotionEvent::parseEventParams(evt);

        void* retVal =  MouseMotionEvent::handleEvent("SystemEvent.MOUSEMOTION", evt, params);

        delete params;
        return retVal;
      }

      static void* handleEvent(const char* name, SDL_MouseMotionEvent, MouseMotionEventParams* params) {
        void* retVal = (void*)true;

        EventCallbackRecord* rec = _eventCallbacks->get(name);

        if (rec) {
          void*(*callback)(void*) = rec->method;

          params->data = rec->input;
          retVal = callback((void*)params);
        }

        return retVal;
      }

  };

#endif
