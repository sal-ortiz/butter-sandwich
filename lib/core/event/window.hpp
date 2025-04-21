
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
        params->context = NULL;   // set later from callback record

        params->horz = evt.data1;
        params->vert = evt.data2;

        return params;
      }


    public:

      static void* parse(SDL_WindowEvent evt) {
        WindowEventParams* params = WindowEvent::parseEventParams(evt);

        switch (evt.event) {

          case SDL_WINDOWEVENT_CLOSE:
            handleEvent("WindowEvent.CLOSED", evt, params);
            break;

          case SDL_WINDOWEVENT_MOVED:
            handleEvent("WindowEvent.MOVED", evt, params);
            break;

          case SDL_WINDOWEVENT_RESIZED:
            handleEvent("WindowEvent.RESIZED", evt, params);
            break;

        }

        delete params;

        return NULL;
      }

      static void* handleEvent(const char* name, SDL_WindowEvent evt, WindowEventParams* params) {
        EventCallbackRecord* rec = _eventCallbacks->get(name);

        if (rec) {
          void*(*callback)(WindowEventParams*) = (void*(*)(WindowEventParams*))(rec->method);

          params->context = rec->context;

          return callback(params);
        }

        return NULL;
      }

  };

#endif




