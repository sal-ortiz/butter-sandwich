
#include <assert.h>
#include <stdlib.h>
#include "../../src/core/tools.h"

#define _TEST_HASHCODE_NUMBER_OF_PASSES   0xf


bool test_hashCode(){
  unsigned long int* hashCodeList;
  unsigned char numPasses = _TEST_HASHCODE_NUMBER_OF_PASSES;

  hashCodeList = new unsigned long int[_TEST_HASHCODE_NUMBER_OF_PASSES];

  for (unsigned long int genIdx = 1; genIdx <= numPasses; genIdx++) {
    const char* genIdxStr = int_to_str(genIdx);

    hashCodeList[genIdx] = hashCode(genIdxStr);
    assert( hashCodeList[genIdx] == hashCode(genIdxStr) );
  }


  for (unsigned long int baseIdx = 1; baseIdx <= numPasses; baseIdx++) {
    unsigned long int matchCount = 0;

    for (unsigned long int cmpIdx = 1; cmpIdx <= numPasses; cmpIdx++) {
      const char* baseIdxStr = int_to_str(baseIdx);

      if (hashCode(baseIdxStr) == hashCodeList[cmpIdx]) {
        matchCount++;
      }

    }

    assert( matchCount <= 1 );
  }

  return true;
}

bool test_array(){
  int* ary;

  ary = (int*)array(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
  for (unsigned long int idx = 0; idx < 10; idx++) {
    assert( ary[idx] == idx );
  }

  ary = (int*)array(9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
  for (unsigned long int idx = 0; idx < 10; idx++) {
    assert( ary[idx] == 9 - idx );
  }

  return true;
}


int main( int argc, char *argv[] ){

  assert( test_hashCode() == true );
  assert( test_array() == true );

  return 0x0000;  // EXIT_SUCCESS;
}
