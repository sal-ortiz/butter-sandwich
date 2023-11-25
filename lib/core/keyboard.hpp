
#ifndef _KEYBOARD_INPUT_HPP

  #define _KEYBOARD_INPUT_HPP

  #include <SDL2/SDL.h>

  #include "./list.hpp"


  struct KeyboardStateEntry {
    bool isPressed;       // false = released, true = pressed
    time_t timestamp;     // last action timestamp
    unsigned char code;   // scancode
  };

  List<KeyboardStateEntry*>* keyboardState/* = new List<KeyboardStateEntry*>()*/;

  class KeyboardInput {

    private:

      static const unsigned int DELAY = 8;  // ms

      static KeyboardStateEntry* getState(unsigned char scanCode) {
        KeyboardStateEntry* entry = keyboardState->get(scanCode);

        return entry;
      }


    public:

      static void initialize() {
        keyboardState = new List<KeyboardStateEntry*>();
      }

      static void deinitialize() {
        unsigned long int len = keyboardState->getLength();

        for (unsigned long int idx = 0; idx < len; idx++) {
          KeyboardStateEntry* entry = keyboardState->get(idx);

          delete entry;
        }

        delete keyboardState;
      }


      static void setState(unsigned char scanCode, bool state) {
        KeyboardStateEntry* entry = keyboardState->get(scanCode);

        if (entry == NULL) {
          entry = new KeyboardStateEntry();

          keyboardState->set(scanCode, entry);
        }

        if (entry->isPressed != state) {
          entry->timestamp = SDL_GetTicks();
        }

        entry->isPressed = state;
        entry->code = scanCode;
      }

      static bool isPressed(unsigned char scanCode) {
        const KeyboardStateEntry* state = KeyboardInput::getState(scanCode);

        if (state == NULL) {
          return false;
        }

        unsigned long int delayTimestamp = state->timestamp + KeyboardInput::DELAY;
        bool isPressed = state->isPressed;

        return isPressed && (SDL_GetTicks() < delayTimestamp);
      }

      static bool isHeld(unsigned char scanCode) {
        const KeyboardStateEntry* state = KeyboardInput::getState(scanCode);

        if (state == NULL) {
          return false;
        }

        unsigned long int delayTimestamp = state->timestamp + KeyboardInput::DELAY;
        bool isPressed = state->isPressed;

        return isPressed && (SDL_GetTicks() > delayTimestamp);
      }

      static bool isReleased(unsigned char scanCode) {
        const KeyboardStateEntry* state = KeyboardInput::getState(scanCode);

        if (state == NULL) {
          return false;
        }

        unsigned long int delayTimestamp = state->timestamp + KeyboardInput::DELAY;
        bool isPressed = state->isPressed;

        return !isPressed && (SDL_GetTicks() < delayTimestamp);
      }

  };

#endif
