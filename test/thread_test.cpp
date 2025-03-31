

#include <time.h>
#include <stdio.h>
#include <cstddef>

#include <SDL2/SDL.h>

#include "../lib/core/thread.hpp"



int32_t funcOne(void*) {
  printf("\n\n\nTHREAD ONE FUNC START....\n");

  SDL_Delay(3000);

  printf("....COMPLETED ONE!!!\n");

  return 0;
}

int32_t funcTwo(void*) {
  printf("\n\n\nTHREAD TWO FUNC START....\n");

  SDL_Delay(4000);

  printf("....COMPLETEd TWO!!!\n");

  return 0;
}

#include <stdarg.h>
void poopOne(int n, ...) {

  va_list args;

  //int n;
  //int k;

  va_start(args, n);



  printf("%d.", n);
  //printf("%d.", k);
  printf("%d.", va_arg(args, int));
  printf("%d.", va_arg(args, int));
  printf("%d.", va_arg(args, int));
  printf("%d.", va_arg(args, int));
  printf("%d.", va_arg(args, int));
  printf("%d.", va_arg(args, int));
  printf("%d.", va_arg(args, int));
  printf("\n");

  va_end(args);
}

void poopTwo(int n, ...) {

  va_list args;

  va_start(args, n);

  poopOne(20, args);
}



int main() {

  poopOne(1,2,3, 4, 5, 6, 7, 8);
  //poopTwo(1,2,3, 4, 5, 6, 7, 8);

  Thread* threadOne = new Thread();
  Thread* threadTwo = new Thread();

  time_t timestamp = time(NULL);

  printf("\n====================================================");

  threadOne->execute(funcOne);
  threadTwo->execute(funcTwo);

  //threadOne->wait();

  threadOne->wait();
  threadTwo->wait();

  printf("\n");

  printf("\n====================================================\n\n");

  //SDL_Delay(5000);


  delete threadOne;
  delete threadTwo;
}
