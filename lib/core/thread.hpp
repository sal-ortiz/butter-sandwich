
#ifndef _THREAD_HPP

  #define _THREAD_HPP

  #include <string.h>

  #include <SDL2/SDL.h>

  //#include "../tools/identifier.hpp"


  struct ThreadParams {
    void* thread;   // when seperating header and impl files, change this to a Thread obj
    void*(*func)(void*, void*, void*);

    void* dataOne;
    void* dataTwo;
    void* dataThree;
  };

  class Thread {

    private:

      SDL_Thread* threadObj;
      SDL_mutex* mutexObj;
      SDL_cond* conditionObj;

      void*(*func)(void*, void*, void*);

      //static const uint8_t ID_LENGTH = 18;

      static int32_t threadFunc(void* data) {
        ThreadParams* parsedData = reinterpret_cast<ThreadParams*>(data);
        Thread* thread = reinterpret_cast<Thread*>(parsedData->thread);

        thread->waitForTrigger();

        thread->lock();

        parsedData->func(
          parsedData->dataOne,
          parsedData->dataTwo,
          parsedData->dataThree
        );

        thread->unlock();

        SDL_DestroyCond(thread->conditionObj);

        thread->conditionObj = SDL_CreateCond();

        return (int32_t)NULL;
      }


    public:

      Thread() {
        this->mutexObj = SDL_CreateMutex();
        //this->conditionObj = SDL_CreateCond();
      }

      ~Thread() {
        SDL_UnlockMutex(this->mutexObj);
        SDL_DestroyMutex(this->mutexObj);

        SDL_DestroyCond(this->conditionObj);
      }

      //static void generateIdentifier(char* dest) {
      //  uint32_t runtimeId = IdentifierTools::generate();
      //
      //  sprintf(dest, "thread-%.10u", runtimeId);
      //}

      void execute(void*(*func)(void*, void*, void*), void* inpOne=NULL, void* inpTwo=NULL, void* inpThree=NULL) {
        ThreadParams* params = new ThreadParams();

        params->thread = (void*)this;
        params->func = func;

        params->dataOne = inpOne;
        params->dataTwo = inpTwo;
        params->dataThree = inpThree;

        this->threadObj = SDL_CreateThread(Thread::threadFunc, NULL, params);
      }

      void detach() {
        SDL_DetachThread(this->threadObj);
      }

      void wait() {
        //SDL_CondWait(this->conditionObj, this->mutexObj);
        SDL_WaitThread(this->threadObj, NULL);
      }

      void wait(Thread* thread) {
        //SDL_CondWait(thread->conditionObj, this->mutexObj);
        SDL_WaitThread(thread->threadObj, NULL);
      }

      void lock() {
        SDL_LockMutex(this->mutexObj);
      }

      void unlock() {
        SDL_UnlockMutex(this->mutexObj);
      }

      void waitForTrigger() {
        SDL_CondWait(this->conditionObj, this->mutexObj);
      }

      void trigger() {
        SDL_CondSignal(this->conditionObj);
      }

  };

#endif
