
#ifndef _EVENT_HPP

  #define _EVENT_HPP

  #include <stdint.h>

  #include <SDL2/SDL.h>

  #include <core/map/hash_map.hpp>
  #include <core/event/window.hpp>
  #include <core/event/application.hpp>
  #include <core/event/keyboard.hpp>
  #include <core/event/mouse_motion.hpp>
  #include <core/event/mouse_button.hpp>
  #include <core/event/user.hpp>


  class Event {

    public:

      static void initialize() {
        _eventCallbacks = new TreeMap<EventCallbackRecord*>();
      }

      static void deinitialize() {
        List<EventCallbackRecord*>* vals = _eventCallbacks->getValues();

        uint32_t valsLen = vals->getLength();

        for (uint32_t idx = 0; idx < valsLen; idx++) {
          EventCallbackRecord* val = vals->get(idx);

          delete val;
        }

        delete vals;
        delete _eventCallbacks;
      }

      static void on(const char* id, void*(*callback)(EventParamsBase*), void* context=NULL) {
        EventCallbackRecord* entry = new EventCallbackRecord();

        entry->method = callback;
        entry->context = context;

        _eventCallbacks->set(id, entry);
      }

      static void* evaluate() {
        SDL_Event evt;
        void* retVal = (void*)true;

        int32_t res = SDL_PollEvent(&evt);

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

      //static void pushEvent(int32_t code, void* dataOne=(void*)NULL, void* dataTwo=(void*)NULL) {
      //  SDL_Event* event;
      //
      //  event->type = SDL_USEREVENT;
      //  event->user.code = code;
      //  event->user.data1 = dataOne;
      //  event->user.data2 = dataTwo;
      //
      //  SDL_PushEvent(event);
      //
      //  delete event;
      //}

  };

#endif
