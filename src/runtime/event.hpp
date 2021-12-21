

#ifndef _EVENT_HPP
  #define _EVENT_HPP

  #include <SDL2/SDL.h>

  #include "../core/dict.hpp"
  #include "./event/base.hpp"

  Dict<bool(*)()> _callbacks;


  class Event {

//    private:



    public:

      static bool poll() {
        SDL_Event evt;

        SDL_PollEvent(&evt);

        return parse(evt);
      }

      static void on(const char* id, bool (*callback)()) {
        _callbacks.set(id, callback);
      }

      static bool parse(SDL_Event evt) {
        bool(*callback)() = _callbacks.get("QUIT");
        bool retVal = true;

        if (evt.type == SDL_QUIT) {
          callback = _callbacks.get("QUIT");

          retVal = callback();

        } else if (evt.type == SDL_WINDOWEVENT) {

          switch (evt.window.event) {

            case SDL_WINDOWEVENT_CLOSE:
              callback = _callbacks.get("CLOSE");

              retVal = callback();
              break;

          }

        }

        return retVal;
      }

  };

#endif
