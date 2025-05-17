
#ifndef _LOGGER_TOOLS

  #define _LOGGER_TOOLS

  //#include <string.h>
  #include <stdio.h>

  #include <SDL2/SDL.h>

  #include <tools/logger/banner.hpp>


  static bool initialized = false;

  class Logger {

    public:

      template <typename ... Args>
      static void print(const char* fmtInp, Args...args) {


        if (initialized != true) {
          Banner::print(0, 0, 1, "dev", "1970010100000");

          initialized = true;
        }

        uint32_t strLen = 1025;

        uint32_t timestamp = SDL_GetTicks();
        char* fmtStr = (char*)malloc(strLen);

        sprintf(fmtStr, "\e[2;37m[\e[0;37m%d\e[2;37m]\e[0;97m %s\e[0m\n", timestamp, fmtInp);
        //sprintf(fmtStr, "[%d] %s\n", timestamp, fmtInp);

        fflush(stdout);

        printf(fmtStr, args...);

        free(fmtStr);
      }


  };

#endif
