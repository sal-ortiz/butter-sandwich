
#ifndef _THREAD_HPP

  #define _THREAD_HPP

  #include <string.h>

  #include <SDL2/SDL.h>

  #include "./list.hpp"
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
      SDL_mutex* mutex;
      //SDL_cond* condition;

      void*(*func)(void*, void*, void*);

      static const uint8_t ID_LENGTH = 18;

      static int32_t threadFunc(void* data) {
        ThreadParams* parsedData = reinterpret_cast<ThreadParams*>(data);
        Thread* thread = reinterpret_cast<Thread*>(parsedData->thread);

        thread->lock();
        parsedData->func(
          parsedData->dataOne,
          parsedData->dataTwo,
          parsedData->dataThree
        );
        thread->unlock();

        //thread->triggerCondition();

        return (int32_t)NULL;
      }


    public:

      Thread() {
        this->mutex = SDL_CreateMutex();
        //this->condition = SDL_CreateCond();
      }

      ~Thread() {
        SDL_UnlockMutex(this->mutex);
        SDL_DestroyMutex(this->mutex);
        //SDL_DestroyCond(this->condition);
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
        //SDL_CondWait(this->condition, this->mutex);
        SDL_WaitThread(this->threadObj, NULL);
      }

      //void wait(Thread* thread) {
      //  //SDL_CondWait(thread->condition, this->mutex);
      //  SDL_WaitThread(thread->threadObj, NULL);
      //}

      void lock() {
        SDL_LockMutex(this->mutex);
      }

      void unlock() {
        SDL_UnlockMutex(this->mutex);
      }

      //void triggerCondition() {
      //  SDL_CondSignal(this->condition);
      //}

  };

#endif
