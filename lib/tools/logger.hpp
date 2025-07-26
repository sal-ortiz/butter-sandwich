
#ifndef _LOGGER_TOOLS

  #define _LOGGER_TOOLS

  //#include <string.h>
  #include <stdio.h>

  #include <SDL2/SDL.h>

  #include <tools/logger/banner.hpp>

  # define MAJ_VER      0
  # define MIN_VER      0
  # define PATCH_VER    1
  # define ENV_VER      "dev"
  # define BUILD_NUM    "1970010100000"


  static bool initialized = false;

  class Logger {

    public:

      template <typename ... Args>
      static void info(const char* fmtInp, Args...args) {

        if (initialized != true) {
          Banner::print(MAJ_VER, MIN_VER, PATCH_VER, ENV_VER, BUILD_NUM);

          initialized = true;
        }

        uint32_t strLen = 1025;

        uint32_t timestamp = SDL_GetTicks();
        char* fmtStr = (char*)malloc(strLen);

        sprintf(fmtStr, "\e[2;37m[\e[0;37m%d\e[2;37m]\e[0;37m %s\e[0m\n", timestamp, fmtInp);

        fflush(stdout);

        printf(fmtStr, args...);

        free(fmtStr);
      }

      template <typename ... Args>
      static void warning(const char* fmtInp, Args...args) {

        if (initialized != true) {
          Banner::print(0, 0, 1, "dev", "1970010100000");

          initialized = true;
        }

        uint32_t strLen = 1025;

        uint32_t timestamp = SDL_GetTicks();
        char* fmtStr = (char*)malloc(strLen);

        sprintf(fmtStr, "\e[0;37m[\e[1;97m%d\e[0;37m]\e[1;93m %s\e[0m\n", timestamp, fmtInp);

        fflush(stdout);

        printf(fmtStr, args...);

        free(fmtStr);
      }

      template <typename ... Args>
      static void error(const char* fmtInp, Args...args) {

        if (initialized != true) {
          Banner::print(0, 0, 1, "dev", "1970010100000");

          initialized = true;
        }

        uint32_t strLen = 1025;

        uint32_t timestamp = SDL_GetTicks();
        char* fmtStr = (char*)malloc(strLen);

        sprintf(fmtStr, "\e[0;37m[\e[1;97m%d\e[0;37m]\e[1;91m %s\e[0m\n", timestamp, fmtInp);

        fflush(stdout);

        printf(fmtStr, args...);

        free(fmtStr);
      }


  };

#endif
