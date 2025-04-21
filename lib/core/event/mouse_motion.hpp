

#ifndef _MOUSE_MOTION_EVENT_HPP

  #define _MOUSE_MOTION_EVENT_HPP

  #include <stdint.h>

  #include <core/event/base.hpp>


  struct MouseMotionEventParams: EventParamsBase {
    uint32_t mouseId;

    bool leftBtnIsPressed;
    bool midBtnIsPressed;
    bool rightBtnIsPressed;

    int32_t horzPos;
    int32_t vertPos;

    int32_t horzOffset;
    int32_t vertOffset;
  };


  class MouseMotionEvent: public EventBase {

    private:

      static MouseMotionEventParams* parseEventParams(SDL_MouseMotionEvent evt) {
        MouseMotionEventParams* params = new MouseMotionEventParams();

        params->timestamp = evt.timestamp;
        params->windowId = evt.windowID;
        params->context = NULL;   // // set later from callback record

        params->mouseId = evt.which;
        //params->state = evt.state;

        params->horzPos = evt.x;
        params->vertPos = evt.y;
        params->horzOffset = evt.xrel;
        params->vertOffset = evt.yrel;

        return params;
      }


    public:

      static void* parse(SDL_MouseMotionEvent evt) {
        MouseMotionEventParams* params = MouseMotionEvent::parseEventParams(evt);

        MouseMotionEvent::handleEvent("SystemEvent.MOUSEMOTION", evt, params);

        delete params;

        return NULL;
      }

      static void* handleEvent(const char* name, SDL_MouseMotionEvent, MouseMotionEventParams* params) {
        EventCallbackRecord* rec = _eventCallbacks->get(name);

        if (rec) {
          void*(*callback)(MouseMotionEventParams*) = (void*(*)(MouseMotionEventParams*))rec->method;

          params->context = rec->context;

          return callback(params);
        }

        return NULL;
      }

  };

#endif
