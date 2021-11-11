#include <assert.h>
#include "../../src/core/array.hpp"

Array<unsigned char> ary(10);



int main(int argc, char *argv[]){
  assert( ary.length() == 10 );

  //assert( (unsigned long int)_arrayIndexPtr(0, 10, sizeof(unsigned long int)) == 80 );
  //assert( (unsigned long int)_arrayIndexPtr(40, 10, sizeof(unsigned long int)) == 120 );

  ary.fill(64);
  for (unsigned char index=0; index < ary.length(); index++)   assert( ary[index] == 64 );

  ary.fill(0);
  for (unsigned char index=0; index < ary.length(); index++)   assert( ary[index] == 0 );

  ary.fill(255, 3, 3);
  for (unsigned char index=0; index < 3; index++)              assert( ary[index] == 0 );
  for (unsigned char index=3; index < 6; index++)              assert( ary[index] == 255 );
  for (unsigned char index=6; index < ary.length(); index++)   assert( ary[index] == 0 );

  ary.push(127);
    assert( ary.length() == 11 );
    assert( ary[ary.length()-1] == 127 );

  ary.push(63);
    assert( ary.length() == 12 );
    assert( ary[ary.length()-1] == 63 );

  ary.push(31);
    assert( ary.length() == 13 );
    assert( ary[ary.length()-1] == 31 );

  return 0x0000;  // EXIT_SUCCESS;
}
