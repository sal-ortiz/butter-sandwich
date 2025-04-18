
#ifndef _WINDOW_EVENT_HPP

  #define _WINDOW_EVENT_HPP

  #include <stdint.h>

  #include <core/event/base.hpp>


  struct WindowEventParams: EventParamsBase {
    int32_t horz;
    int32_t vert;
  };


  class WindowEvent: public EventBase {

    private:

      static WindowEventParams* parseEventParams(SDL_WindowEvent evt) {
        WindowEventParams* params = new WindowEventParams();

        params->timestamp = evt.timestamp;
        params->windowId = evt.windowID;
        params->data = NULL;

        params->horz = evt.data1;
        params->vert = evt.data2;

        return params;
      }


    public:

      static void* parse(SDL_WindowEvent evt) {
        void* retVal = (void*)true;

        WindowEventParams* params = WindowEvent::parseEventParams(evt);

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

        delete params;
        return retVal;
      }

      static void* handleEvent(const char* name, SDL_WindowEvent evt, WindowEventParams* params) {
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




