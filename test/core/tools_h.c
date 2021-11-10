
#include <assert.h>
#include <stdlib.h>
#include "../../src/core/tools.h"

#define _TEST_HASHCODE_NUMBER_OF_PASSES   0xf





bool test_hashCode(){

  // populate our list, verifying entries per pass.
  unsigned long int* hashCodeList = new unsigned long int[_TEST_HASHCODE_NUMBER_OF_PASSES];
  for( unsigned long int generatorIndex = 1; generatorIndex <= _TEST_HASHCODE_NUMBER_OF_PASSES; generatorIndex++ ){
    hashCodeList[ generatorIndex ] = hashCode( int_to_str(generatorIndex) );
    assert( hashCodeList[ generatorIndex ] == hashCode( int_to_str(generatorIndex) ) );
  }

  // verify contents, validating for repetitions.
  for( unsigned long int baseIndex = 1; baseIndex <= _TEST_HASHCODE_NUMBER_OF_PASSES; baseIndex++ ){
    unsigned long int matchCount = 0;
    for( unsigned long int compareIndex = 1; compareIndex <= _TEST_HASHCODE_NUMBER_OF_PASSES; compareIndex++ )
      if( hashCode( int_to_str(baseIndex) ) == hashCodeList[compareIndex] )   matchCount++;

    assert( matchCount <= 1 );
  }

  return true;
} // ---------------------------------------------------------------------------


bool test_array(){

  int* ary;
  ary = (int*)array( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 );
  for( unsigned long int index = 0; index < 10; assert( ary[index] == index++ ) );

  ary = (int*)array( 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 );  // fill the array.
  for( unsigned long int index = 0; index < 10; assert( ary[index] == 9-index++ ) );

  return true;
} // ---------------------------------------------------------------------------



int main( int argc, char *argv[] ){

  //assert( test_hashCode() == true );
  assert( test_array() == true );

  return 0x0000;  // EXIT_SUCCESS;
}
