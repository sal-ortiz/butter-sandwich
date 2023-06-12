
#ifndef _CORE_EVENT_HPP

  #define _CORE_EVENT_HPP

  #include <SDL2/SDL.h>

  #include "./event/window.hpp"
  #include "./event/application.hpp"
  #include "./event/keyboard.hpp"
  #include "./event/mouse_motion.hpp"
  #include "./event/mouse_button.hpp"
  #include "./event/user.hpp"


  class Event {

    public:

      static void on(const char* id, void*(*callback)(void*), void* inp) {
        CallbackRecord entry = { callback, inp };

        _callbacks.set(id, entry);
      }

      static void* evaluate() {
        SDL_Event evt;
        void* retVal = (void*)true;

        int res = SDL_PollEvent(&evt);

        if (res == 0) {
          // no events to pull.
          return (void*)NULL;
        }

        switch(evt.type) {

          case SDL_QUIT:
            retVal = ApplicationEvent::parse(evt.quit);
            break;

          case SDL_WINDOWEVENT:
            retVal = WindowEvent::parse(evt.window);
            break;

          case SDL_KEYDOWN:
          case SDL_KEYUP:
            retVal = KeyboardEvent::parse(evt.key);
            break;

          case SDL_MOUSEMOTION:
            retVal = MouseMotionEvent::parse(evt.motion);
            break;

          case SDL_MOUSEBUTTONDOWN:
          case SDL_MOUSEBUTTONUP:
            retVal = MouseButtonEvent::parse(evt.button);
            break;

          case SDL_USEREVENT:
            retVal = UserEvent::parse(evt.user);
            break;

        }

        return retVal;
      }

      static void pushEvent(signed long int code, void* dataOne=(void*)NULL, void* dataTwo=(void*)NULL) {

        SDL_Event* event = new SDL_Event();

        event->type = SDL_USEREVENT;
        event->user.code = code;
        event->user.data1 = dataOne;
        event->user.data2 = dataTwo;

        SDL_PushEvent(event);
      }

  };

#endif
