
#ifndef _EVENT_HPP

  #define _EVENT_HPP

  #include <SDL2/SDL.h>

  #include "../core/dict.hpp"
  #include "./event/window.hpp"
  #include "./event/application.hpp"
  #include "./event/keyboard.hpp"


  class Event {

    public:

      static void on(const char* id, void*(*callback)(void*), void* inp) {
        CallbackRecord entry = { callback, inp };

        _callbacks.set(id, entry);
      }

      static void* evaluate() {
        SDL_Event evt;
        void* retVal = (void*)true;

        SDL_PollEvent(&evt);

        if (evt.type == SDL_QUIT) {
          retVal = ApplicationEvent::parse(evt.quit);
        } else if (evt.type == SDL_WINDOWEVENT) {
          retVal = WindowEvent::parse(evt.window);
        } else if ((evt.type == SDL_KEYDOWN) || (evt.type == SDL_KEYUP))  {
          retVal = KeyboardEvent::parse(evt.key);
        }

        return retVal;
      }

  };

#endif
