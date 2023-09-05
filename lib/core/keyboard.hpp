
#ifndef _KEYBOARD_INPUT_HPP

  #define _KEYBOARD_INPUT_HPP

  #include <SDL2/SDL.h>

  #include "./list.hpp"


  struct KeyboardStateEntry {
    bool isPressed;       // false = released, true = pressed
    time_t timestamp;     // last action timestamp
    unsigned char code;   // scancode
  };

  List<KeyboardStateEntry*>* keyboardState = new List<KeyboardStateEntry*>();

  class KeyboardInput {

    public:

      static const unsigned int DELAY = 8;  // ms

      static void updateState(unsigned char scanCode, bool state) {
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

      static KeyboardStateEntry* getState(unsigned char scanCode) {
        KeyboardStateEntry* entry = keyboardState->get(scanCode);

        if (entry == NULL) {
          entry = new KeyboardStateEntry();

          entry->isPressed = 0;
          entry->timestamp = 0;
          entry->code = scanCode;
        }

        return entry;
      }

      static bool isPressed(unsigned char scanCode) {
        const KeyboardStateEntry* state = KeyboardInput::getState(scanCode);

        return state->isPressed == true && SDL_GetTicks() < (state->timestamp + KeyboardInput::DELAY);
      }

      static bool isHeld(unsigned char scanCode) {
        const KeyboardStateEntry* state = KeyboardInput::getState(scanCode);

        return state->isPressed == true && SDL_GetTicks() > (state->timestamp + KeyboardInput::DELAY);
      }

      static bool isReleased(unsigned char scanCode) {
        const KeyboardStateEntry* state = KeyboardInput::getState(scanCode);

        return state->isPressed == false && SDL_GetTicks() < (state->timestamp + KeyboardInput::DELAY);
      }

  };

#endif
