
#ifndef _USER_EVENT_HPP

  #define _USER_EVENT_HPP

  #include <stdint.h>

  #include <core/event/base.hpp>


  const int32_t PRESENT_WINDOW = 0x0001;
  const int32_t RENDER_ELEMENT = 0x0002;


  struct UserEventParams: EventParamsBase {
    // intentionally left blank.
  };


  class UserEvent: public EventBase {

    private:

      static UserEventParams* parseEventParams(SDL_UserEvent evt) {
        UserEventParams* params = new UserEventParams();

        params->timestamp = evt.timestamp;
        params->windowId = evt.windowID;
        params->data = NULL;

        return params;
      }


    public:

      static void* parse(SDL_UserEvent evt) {
        UserEventParams* params = UserEvent::parseEventParams(evt);

        switch (evt.code) {
          //case RENDER_ELEMENT:
          //  handleEvent("UserEvent.RENDER", evt, params);
          //  break;

          case PRESENT_WINDOW:
            handleEvent("UserEvent.WINDOWPRESENT", evt, params);
            break;

        }

        delete params;

        return NULL;
      }

      static void* handleEvent(const char* name, SDL_UserEvent evt, UserEventParams* params) {
        EventCallbackRecord* rec = _eventCallbacks->get(name);

        if (rec) {
          void*(*callback)(UserEventParams*) = (void*(*)(UserEventParams*))(rec->method);

          params->data = rec->input;

          return callback(params);
        }

        return NULL;
      }

  };


#endif
