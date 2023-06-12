
#ifndef _EVENT_USER_HPP

  #define _EVENT_USER_HPP

  #include "./base.hpp"


  const signed long int PRESENT_WINDOW = 0x0001;
  const signed long int RENDER_ELEMENT = 0x0002;


  struct UserEventParams: EventParamsBase {
    // intentionally left blank.
  };


  class UserEvent: public EventBase {

    private:

      static UserEventParams parseEventParams(SDL_UserEvent evt) {
        UserEventParams params = {

        };

        return params;
      }

    public:

      static void* parse(SDL_UserEvent evt) {
        void* retVal = (void*)true;

        UserEventParams params = UserEvent::parseEventParams(evt);

        switch (evt.code) {
          //case RENDER_ELEMENT:
          //  retVal = handleEvent("UserEvent.RENDER", evt, params);
          //  break;

          case PRESENT_WINDOW:
            retVal = handleEvent("UserEvent.WINDOWPRESENT", evt, params);
            break;

        }

        return retVal;
      }

      static void* handleEvent(const char* name, SDL_UserEvent evt, UserEventParams params) {
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
