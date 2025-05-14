#ifndef _IDENTIFIER_TOOLS

  #define _IDENTIFIER_TOOLS

  #include <time.h>
  #include <stdlib.h>

  #include <SDL2/SDL.h>

  static uint32_t ID_TOOLS_MAGIC_NUMBER = 1;

  class Identifier {

    public:

      static uint32_t generate() {
        time_t timestamp = time(NULL);

        srand(timestamp);

        ID_TOOLS_MAGIC_NUMBER += (rand() * timestamp) * 31337;

        return ID_TOOLS_MAGIC_NUMBER & 0x7fffffff;
      }

  };

#endif
