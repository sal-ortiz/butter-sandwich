
#ifndef _KEYBOARD_INPUT_HPP

  #define _KEYBOARD_INPUT_HPP

  #include <SDL2/SDL.h>

  #include "./list.hpp"


  struct KeyboardStateEntry {
    bool isPressed;       // false = released, true = pressed
    time_t timestamp;     // last action timestamp
    uint8_t code;   // scancode
  };

  List<KeyboardStateEntry*>* keyboardState/* = new List<KeyboardStateEntry*>()*/;

  class KeyboardInput {

    private:

      static const uint16_t DELAY = 8;  // ms

      static KeyboardStateEntry* getState(uint8_t scanCode) {
        KeyboardStateEntry* entry = keyboardState->get(scanCode);

        return entry;
      }


    public:

      static void initialize() {
        keyboardState = new List<KeyboardStateEntry*>();
      }

      static void deinitialize() {
        uint32_t len = keyboardState->getLength();

        for (uint32_t idx = 0; idx < len; idx++) {
          KeyboardStateEntry* entry = keyboardState->get(idx);

          delete entry;
        }

        delete keyboardState;
      }


      static void setState(uint8_t scanCode, bool state) {
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

      static bool isPressed(uint8_t scanCode) {
        const KeyboardStateEntry* state = KeyboardInput::getState(scanCode);

        if (state == NULL) {
          return false;
        }

        uint32_t delayTimestamp = state->timestamp + KeyboardInput::DELAY;
        bool isPressed = state->isPressed;

        return isPressed && (SDL_GetTicks() < delayTimestamp);
      }

      static bool isHeld(uint8_t scanCode) {
        const KeyboardStateEntry* state = KeyboardInput::getState(scanCode);

        if (state == NULL) {
          return false;
        }

        uint32_t delayTimestamp = state->timestamp + KeyboardInput::DELAY;
        bool isPressed = state->isPressed;

        return isPressed && (SDL_GetTicks() > delayTimestamp);
      }

      static bool isReleased(uint8_t scanCode) {
        const KeyboardStateEntry* state = KeyboardInput::getState(scanCode);

        if (state == NULL) {
          return false;
        }

        uint32_t delayTimestamp = state->timestamp + KeyboardInput::DELAY;
        bool isPressed = state->isPressed;

        return !isPressed && (SDL_GetTicks() < delayTimestamp);
      }

  };

#endif
