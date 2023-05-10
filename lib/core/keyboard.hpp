
#ifndef _KEYBOARD_INPUT_HPP

  #define _KEYBOARD_INPUT_HPP

  #include <SDL2/SDL.h>


  const unsigned char* _prevKeyboardState;
  const unsigned char* _curKeyboardState;


  class KeyboardInput {
    // TODO: _prevKeyboardState doesn't actually work so we isReleqased() doesn't work.

    public:

      static void updateState() {
        int numKeys = 256;

        _prevKeyboardState = _curKeyboardState;
        _curKeyboardState = SDL_GetKeyboardState(&numKeys);
      }

      static const unsigned char* getCurrentState() {
        return _curKeyboardState;
      }

      static const unsigned char* getPreviousState() {
        return _prevKeyboardState;
      }

      static bool isPressed(unsigned char scanCode) {
        const unsigned char* state = KeyboardInput::getCurrentState();

        if (state[scanCode] != 0) {
          return true;
        }

        return false;
      }

      static bool wasPressed(unsigned char scanCode) {
        const unsigned char* prevState = KeyboardInput::getPreviousState();

        if (prevState && prevState[scanCode] != 0) {
          return true;
        }

        return false;
      }

      static bool isHeld(unsigned char scanCode) {

        if (KeyboardInput::isPressed(scanCode) && !KeyboardInput::wasPressed(scanCode)) {
          return true;
        }

        return false;
      }

      static bool isReleased(unsigned char scanCode) {

        if (!KeyboardInput::isPressed(scanCode) && KeyboardInput::wasPressed(scanCode)) {
          printf("SADFASDFSA");
          return true;
        }


        return false;
      }

      static bool isPressed(unsigned char* scanCodes) {
        unsigned char aryLen = sizeof(scanCodes) / sizeof(unsigned char);

        for (unsigned char idx = 0; idx < aryLen; idx++) {
          unsigned char scanCode = scanCodes[idx];

          if (!KeyboardInput::isPressed(scanCode)) {
            return false;
          }

          return true;
        }

      }

      static bool isReleased(unsigned char* scanCodes) {
        unsigned char aryLen = sizeof(scanCodes) / sizeof(unsigned char);

        for (unsigned char idx = 0; idx < aryLen; idx++) {
          unsigned char scanCode = scanCodes[idx];

          if (!KeyboardInput::isReleased(scanCode)) {
            return false;
          }

          return true;
        }

    }

  };

#endif
