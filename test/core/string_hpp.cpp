
#include <assert.h>
#include "../../src/core/string.hpp"




int main( int argc, char *argv[] ){

  String str("twenty-seven bytes of data.");

  assert( *str == *"twenty-seven bytes of data." );
  assert( str.length() == 27 );

  str = "thirteenbytes";

  assert( *str == *"thirteenbytes" );
  assert( str.length() == 13 );

  return 0x0000;  // EXIT_SUCCESS;
}
