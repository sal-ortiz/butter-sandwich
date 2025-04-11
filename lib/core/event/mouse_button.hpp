

#ifndef _MOUSE_BUTTON_EVENT_HPP

  #define _MOUSE_BUTTON_EVENT_HPP

  #include <stdint.h>

  #include <core/event/base.hpp>


  struct MouseButtonEventParams: EventParamsBase {
    uint32_t mouseId;
    uint8_t state;

    uint8_t button;
    uint8_t clicks;

    int32_t horzPos;
    int32_t vertPos;
  };


  class MouseButtonEvent: public EventBase {

    private:

      static MouseButtonEventParams* parseEventParams(SDL_MouseButtonEvent evt) {
        MouseButtonEventParams* params = new MouseButtonEventParams();

        params->timestamp = evt.timestamp;
        params->windowId = evt.windowID;
        params->data = NULL;

        params->mouseId = evt.which;
        params->state = evt.state;

        params->button = evt.button;
        params->clicks = evt.clicks;
        params->horzPos = evt.x;
        params->vertPos = evt.y;

        return params;
      }


    public:

      static void* parse(SDL_MouseButtonEvent evt) {
        MouseButtonEventParams* params = MouseButtonEvent::parseEventParams(evt);

        void* retVal = MouseButtonEvent::handleEvent("SystemEvent.MOUSEBUTTON", evt, params);

        delete params;
        return retVal;
      }

      static void* handleEvent(const char* name, SDL_MouseButtonEvent, MouseButtonEventParams* params) {
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

