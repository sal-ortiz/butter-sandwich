

#ifndef _EVENT_HPP
  #define _EVENT_HPP

  #include <SDL2/SDL.h>

  #include "../core/dict.hpp"
  #include "./event/base.hpp"


  struct CallbackRecord {
    bool(*method)(unsigned long int*);
    unsigned long int* input;
  };

  Dict<CallbackRecord> _callbacks;


  class Event {

//    private:



    public:

      static bool poll() {
        SDL_Event evt;

        SDL_PollEvent(&evt);

        return parse(evt);
      }

      static void on(const char* id, bool(*callback)(unsigned long int*), unsigned long int* inp) {
          CallbackRecord entry = { callback, inp };

        _callbacks.set(id, entry);
      }

      static bool parse(SDL_Event evt) {
        bool retVal = true;

        if (evt.type == SDL_QUIT) {
          CallbackRecord callbackRec = _callbacks.get("QUIT");
          bool(*callback)(unsigned long int*) = callbackRec.method;
          unsigned long int* inp = callbackRec.input;

          retVal = callback(inp);

        } else if (evt.type == SDL_WINDOWEVENT) {

          switch (evt.window.event) {

            case SDL_WINDOWEVENT_CLOSE:
              CallbackRecord callbackRec = _callbacks.get("CLOSE");
              bool(*callback)(unsigned long int*) = callbackRec.method;
              unsigned long int* inp = callbackRec.input;

              retVal = callback(inp);
              break;

          }

        }

        return retVal;
      }

  };

#endif
