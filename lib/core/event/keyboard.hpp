
#ifndef _KEYBOARD_EVENT_HPP

  #define _KEYBOARD_EVENT_HPP

  #include <stdint.h>

  #include "./base.hpp"


  struct KeyboardEventParams: EventParamsBase {
    uint8_t state;  // SDL_PRESSED or SDL_RELEASED
    uint8_t repeat;

    uint32_t scanCode;
    //uint32_t keyCode;

    uint16_t modifier;
  };


  class KeyboardEvent: public EventBase {

    private:

      static KeyboardEventParams* parseEventParams(SDL_KeyboardEvent evt) {
        KeyboardEventParams* params = new KeyboardEventParams();

        params->timestamp = evt.timestamp;
        params->windowId = evt.windowID;
        params->data = NULL;

        params->state = evt.state;
        params->repeat = evt.repeat;

        params->scanCode = evt.keysym.scancode;
        //params->keyCode = evt.keysym.sym;
        params->modifier = evt.keysym.mod;

        return params;
      }


    public:

      static void* parse(SDL_KeyboardEvent evt) {
        KeyboardEventParams* params = KeyboardEvent::parseEventParams(evt);

        void* retVal = KeyboardEvent::handleEvent("SystemEvent.KEYBOARD", evt, params);

        delete params;
        return retVal;
      }

      static void* handleEvent(const char* name, SDL_KeyboardEvent evt, KeyboardEventParams* params) {
        void* retVal = (void*)true;

        if (_eventCallbacks->has(name)) {
          EventCallbackRecord* rec = _eventCallbacks->get(name);

          void*(*callback)(void*) = rec->method;

          params->data = rec->input;

          retVal = callback((void*)params);
        }

        return retVal;
      }

  };

#endif
