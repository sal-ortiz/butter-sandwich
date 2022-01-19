
#ifndef _KEYBOARD_EVENT_HPP

  #define _KEYBOARD_EVENT_HPP


  struct KeyboardEventParams: EventParamsBase {
    unsigned long int windowId;
    unsigned char state;  // SDL_PRESSED or SDL_RELEASED
    unsigned char repeat;

    unsigned long int scancode;
    //unsigned long int keycode;

    unsigned int modifier;
  };


  class KeyboardEvent: public EventBase {

    private:

      static KeyboardEventParams parseEventParams(SDL_KeyboardEvent evt) {
        KeyboardEventParams params = {
          evt.timestamp,
          NULL,

          evt.windowID,
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

      static void* handleEvent(const char* name, SDL_KeyboardEvent, KeyboardEventParams params) {
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
