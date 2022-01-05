

#ifndef _EVENT_HPP
  #define _EVENT_HPP

  #include <SDL2/SDL.h>

  #include "../core/dict.hpp"


  struct CallbackRecord {
    void*(*method)(void*);
    void* input;
  };

  Dict<CallbackRecord> _callbacks;


  class Event {

    public:

      static void* poll() {
        SDL_Event evt;

        SDL_PollEvent(&evt);

        return parse(evt);
      }

      static void on(const char* id, void*(*callback)(void*), void* inp) {
          CallbackRecord entry = { callback, inp };

        _callbacks.set(id, entry);
      }

      static void* parse(SDL_Event evt) {
        void* retVal = (void*)true;

        if (evt.type == SDL_QUIT) {
          CallbackRecord callbackRec = _callbacks.get("QUIT");
          void*(*callback)(void*) = callbackRec.method;
          void* inp = callbackRec.input;

          retVal = callback(inp);

        } else if (evt.type == SDL_WINDOWEVENT) {

          switch (evt.window.event) {

            case SDL_WINDOWEVENT_CLOSE:
              CallbackRecord callbackRec = _callbacks.get("CLOSE");
              void*(*callback)(void*) = callbackRec.method;
              void* inp = callbackRec.input;

              retVal = callback(inp);
              break;

          }

        }

        return retVal;
      }

  };

#endif
