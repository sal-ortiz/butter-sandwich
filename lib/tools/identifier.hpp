#ifndef _IDENTIFIER_TOOLS

  #define _IDENTIFIER_TOOLS

  #include <time.h>
  #include <stdlib.h>

  #include <SDL2/SDL.h>

  uint32_t ID_TOOLS_MAGIC_NUMBER = 1;

  class IdentifierTools {

    public:

      static uint32_t generate() {
        uint32_t timestamp = SDL_GetTicks();

        ID_TOOLS_MAGIC_NUMBER = (ID_TOOLS_MAGIC_NUMBER * rand()) % 0xffffffff;

        return ID_TOOLS_MAGIC_NUMBER;
      }

  };

#endif
