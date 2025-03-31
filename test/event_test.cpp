

#include "../lib/core/event.hpp"
#include <time.h>
#include <stdio.h>
#include <cstddef>


void* func(void* inp) {
  return NULL;
}


int main(int argc, char* argv[]) {
  Event::initialize();

  printf("\n\n====================================================\n");

  Event::on("crap", func, NULL);

  Event::pushEvent(0x00);
  Event::pushEvent(0x01);
  Event::pushEvent(0x02);


  printf("\n====================================================\n\n");

  Event::deinitialize();
}
