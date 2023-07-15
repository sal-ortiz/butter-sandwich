

#ifndef _MOUSE_BUTTON_EVENT_HPP

  #define _MOUSE_BUTTON_EVENT_HPP

  #include "./base.hpp"


  struct MouseButtonEventParams: EventParamsBase {
    unsigned long int mouseId;
    unsigned char state;

    unsigned char button;
    unsigned char clicks;

    signed long int horzPos;
    signed long int vertPos;
  };


  class MouseButtonEvent: public EventBase {

    private:

      static MouseButtonEventParams parseEventParams(SDL_MouseButtonEvent evt) {
        MouseButtonEventParams params = {
          evt.timestamp,
          evt.windowID,
          NULL,

          evt.which,
          evt.state,

          evt.button,
          evt.clicks,
          evt.x,
          evt.y
        };

        return params;
      }


    public:

      static void* parse(SDL_MouseButtonEvent evt) {
        MouseButtonEventParams params = MouseButtonEvent::parseEventParams(evt);

        return MouseButtonEvent::handleEvent("SystemEvent.MOUSEBUTTON", evt, params);
      }

      static void* handleEvent(const char* name, SDL_MouseButtonEvent, MouseButtonEventParams params) {
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

