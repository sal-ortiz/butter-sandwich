
#ifndef _KEYBOARD_INPUT_HPP

  #define _KEYBOARD_INPUT_HPP

  #include <time.h>
  #include <SDL2/SDL.h>

  #include "./list.hpp"


  struct KeyboardStateEntry {
    bool isPressed;         // false = released, true = pressed
    time_t timestamp;       // last action timestamp
    unsigned long int code; // scancode
  };

  List<KeyboardStateEntry*>* keyboardState = new List<KeyboardStateEntry*>();

  class KeyboardInput {

    public:

      static const unsigned int DELAY = 150;  // ms

      static void updateState(unsigned long int scanCode, bool state) {
        KeyboardStateEntry* entry = keyboardState->get(scanCode);

        if (entry == NULL) {
          entry = new KeyboardStateEntry();

          keyboardState->set(scanCode, entry);
        }

        if (entry->isPressed != state) {
          entry->timestamp = time(NULL);
        }

        entry->isPressed = state;
        entry->code = scanCode;
      }

      static KeyboardStateEntry* getState(unsigned long int scanCode) {
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

        return state->isPressed == true && state->timestamp < (time(NULL) + KeyboardInput::DELAY);
      }

      static bool isHeld(unsigned char scanCode) {
        // NOTE: This doesn't actually work.
        const KeyboardStateEntry* state = KeyboardInput::getState(scanCode);

        return state->isPressed == true && state->timestamp > (time(NULL) + KeyboardInput::DELAY);
      }

      static bool isReleased(unsigned char scanCode) {
        // NOTE: This doesn't actually work.
        const KeyboardStateEntry* state = KeyboardInput::getState(scanCode);

        return state->isPressed == false && state->timestamp < (time(NULL) + KeyboardInput::DELAY);
      }

  };

#endif
