
#ifndef _KEYBOARD_EVENT_HPP

  #define _KEYBOARD_EVENT_HPP

  #include "./base.hpp"


  struct KeyboardEventParams: EventParamsBase {
    uint8_t state;  // SDL_PRESSED or SDL_RELEASED
    uint8_t repeat;

    uint32_t scanCode;
    //uint32_t keycode;

    uint16_t modifier;
  };


  class KeyboardEvent: public EventBase {

    private:

      static KeyboardEventParams parseEventParams(SDL_KeyboardEvent evt) {
        KeyboardEventParams params = {
          evt.timestamp,
          evt.windowID,
          NULL,

          evt.state,
          evt.repeat,

          evt.keysym.scancode,
          //evt.keysym.sym,
          evt.keysym.mod
        };

        return params;
      }


    public:

      static void* parse(SDL_KeyboardEvent evt) {
        KeyboardEventParams params = KeyboardEvent::parseEventParams(evt);

        return KeyboardEvent::handleEvent("SystemEvent.KEYBOARD", evt, params);
      }

      static void* handleEvent(const char* name, SDL_KeyboardEvent evt, KeyboardEventParams params) {
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
