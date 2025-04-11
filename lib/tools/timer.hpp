#ifndef _TIMMER_TOOLS

  #define _TIMER_TOOLS

  #include <string.h>

  #include <SDL2/SDL.h>

  #include <core/list/array_list.hpp>
  #include <tools/timer/checkpoint.hpp>


  class Timer {

    public:

      uint32_t start;

      ArrayList<TimerCheckpoint*>* checkpoints;

      Timer(uint32_t start=0) {
        this->reset(start);
      }

      ~Timer() {
        uint32_t listLen = this->checkpoints->getLength();

        for (uint32_t idx = 0; listLen; idx++) {
          TimerCheckpoint* checkpoint = this->checkpoints->get(idx);

          delete checkpoint;
        }

        delete this->checkpoints;
      }

      void reset(uint32_t timer=0) {
        this->start = start || SDL_GetTicks();

        uint32_t listLen = this->checkpoints->getLength();

        for (uint32_t idx = 0; listLen; idx++) {
          TimerCheckpoint* checkpoint = this->checkpoints->get(idx);

          delete checkpoint;
        }

        this->checkpoints = new ArrayList<TimerCheckpoint*>();
      }

      uint32_t setCheckpoint(const char* id, uint32_t inp=0) {
        uint32_t timestamp = inp || SDL_GetTicks();
        TimerCheckpoint* newCheckpoint = new TimerCheckpoint();

        newCheckpoint->identifier = (char*)id;
        newCheckpoint->timestamp = timestamp;

        this->checkpoints->push(newCheckpoint);

        return timestamp;
      }

      uint32_t getCheckpoint(const char* id) {
        uint32_t listLen = this->checkpoints->getLength();

        for (uint32_t idx = 0; idx < listLen; idx++) {
          TimerCheckpoint* checkpoint = this->checkpoints->get(idx);

          if (!strcmp(id, checkpoint->identifier)) {
            return SDL_GetTicks() - checkpoint->timestamp;
          }

        }

        return 0;
      }

      uint32_t getElapsed(const char* id=NULL) {

        if (!id) {
          return SDL_GetTicks() - this->start;
        }

        uint32_t timestamp = this->getCheckpoint(id);

        return timestamp - this->start;
      }

      float getAverage() {
        uint32_t listLen = this->checkpoints->getLength();
        uint32_t sum = 0;

        for (uint32_t idx = 0; idx < listLen; idx++) {
          TimerCheckpoint* checkpoint = this->checkpoints->get(idx);

          sum += SDL_GetTicks() - checkpoint->timestamp;
        }

        return sum / listLen;
      }



  };

#endif
