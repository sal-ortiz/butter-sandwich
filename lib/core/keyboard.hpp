

#include <SDL2/SDL.h>


const unsigned char* _prevKeyboardState;
const unsigned char* _curKeyboardState;


class KeyboardInput {
  // TODO: Add functions for wasPressed()? isHeld()? wasReleased?


  public:

    static const unsigned char* getState() {
      _prevKeyboardState = _curKeyboardState;
      _curKeyboardState = SDL_GetKeyboardState(NULL);

      return _curKeyboardState;
    }

    static bool isPressed(unsigned char scanCode) {
      const unsigned char* state = KeyboardInput::getState();

      if (state[scanCode] != 0) {
        return true;
      }

      return false;
    }

    static bool isHeld(unsigned long int scanCode) {
      const unsigned char* state = KeyboardInput::getState();


      if (KeyboardInput::isPressed(scanCode) && !(_prevKeyboardState[scanCode])) {
        return true;
      }

      return false;
    }

    static bool isReleased(unsigned char scanCode) {
      const unsigned char* state = KeyboardInput::getState();

      if (KeyboardInput::isPressed(scanCode) && !(_prevKeyboardState[scanCode])) {
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
