
#include <assert.h>
#include <stdlib.h>
#include "../../src/core/hash.hpp"
#include "../../src/core/tools.h"


Hash<unsigned char> hsh;

int main( int argc, char *argv[] ){

  for (unsigned char idx = 10; idx > 0; idx--) {
    const char* idxStr = int_to_str(idx);

    assert(
      hsh.set(idxStr, idx) == idx
    );

    assert(
      hsh.get(int_to_str(idx)) == idx
    );
  }

  for (unsigned char idx = 10; idx; idx--) {
    const char* idxStr = int_to_str(idx);

    assert(
      hsh.get(idxStr) == idx
    );
  }

  return 0x0000;  // EXIT_SUCCESS;
}
