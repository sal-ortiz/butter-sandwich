

#include "../lib/core/image.hpp"
#include <time.h>
#include <stdio.h>
#include <cstddef>


void* func(void* inp) {
  return NULL;
}


int main(int argc, char* argv[]) {

  printf("\n\n====================================================\n");

  Image* img = Image::load("../src/assets/asteroid_sheet.png", 0, 0);

  delete img;

  printf("\n====================================================\n\n");

}
