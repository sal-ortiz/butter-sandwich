
#include <assert.h>
#include "../../src/core/base.hpp"


class Inherited: public Base {
  /* intentionally left blank */
};  // class Inherited


Base* baseObj;            // Base is the object.
Inherited* inheritedObj;  // Base is inherited.

int main( int argc, char *argv[] ){

  baseObj = new Base();
  inheritedObj = new Inherited();

  assert( baseObj->getIdentifier() != 0 );
  assert( inheritedObj->getIdentifier() != 0 );
  assert( inheritedObj->getIdentifier() != baseObj->getIdentifier() );

  return 0x0000;  // EXIT_SUCCESS;
}
