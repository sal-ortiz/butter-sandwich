
#ifndef _THREAD_HPP

  #define _THREAD_HPP

  #include <SDL2/SDL.h>


  class Thread {

    private:

      char* identifier;

      int(*func)(void*);

      SDL_Thread* threadObj;
      SDL_mutex* mutexObj;

      static char* generateIdentifier() {
        char* identifier = new char[64];
        time_t timestamp = time(NULL);

        srand(timestamp * rand());

        sprintf(identifier, "thread-%ld", timestamp % (rand() * rand() * rand()));

        return identifier;
      }


    public:

      Thread() {
        this->identifier = Thread::generateIdentifier();
        this->mutexObj = SDL_CreateMutex();
      }

      Thread(int(*func)(void*)) {
        this->identifier = Thread::generateIdentifier();
        this->func = func;
        this->mutexObj = SDL_CreateMutex();
      }

      ~Thread() {
        SDL_UnlockMutex(this->mutexObj);
        SDL_DestroyMutex(this->mutexObj);
      }

      void setFunc() {
        this->func = func;
      }

      void execute(void* data) {
        threadObj = SDL_CreateThread(func, identifier, data);
      }

      void detach() {
        SDL_DetachThread(this->threadObj);
      }

      void wait() {
        SDL_WaitThread(this->threadObj, NULL);
      }

      void lock() {
        SDL_LockMutex(this->mutexObj);
      }

      void unlock() {
        SDL_UnlockMutex(this->mutexObj);
      }

      static void execute(int(*func)(void*), void* data) {
        Thread* thread = new Thread(func);

        thread->execute(data);
        thread->detach();
      }

  };

#endif
