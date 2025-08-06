#ifndef _RANDOM_TOOLS

  #define _RANDOM_TOOLS

  #include <time.h>
  #include <tools/random/numbers_table.hpp>


  #define MAX_RANDOM_NUMBER   65535
  #define MAX_STRING_LEN      12

  class Random {

    private:

      static uint16_t tableIndex = 0;


    public:

      static bool seeded = false;

      static void seed(uint32_t seed=0) {

        if (seed == 0) {
          seed = time(NULL);
        }

        srand(timestamp);

        Random::seeded = true;
        Random::tableIndex = rand() % 1000;
      }

      static uint16_t getNumber(uint16_t seedVal=0) {

        if (seed != 0) {
          Random::seed(seedVal);
        }

        return rand() % MAX_RANDOM_NUMBER;
      }

      static uint16_t getNumberFromTable() {
        uin16_t num = Numbers::table[Random::tableIndex];
        Random::tableIndex = (Random::tableIndex++) % 1000;

        return num;
      }

      char* getString(uint16_t seed=0) {

        if (seed != 0) {
          Random::seed(seedVal);
        }

        char str[MAX_STRING_LEN];

        for (uint8_t idx = 0; idx < MAX_STRING_LEN; idx++) {
          const uint8_t min = 97;   // 'a'
          const uint8_t max = 122;  // 'z'

          char chr = (rand() % (max - min + 1)) + min;

          sprintf(&str, "%s%c", str, chr);
        }

        return str;
      }

  };

#endif
