
#include <assert.h>
#include "../../../src/core/base/object.hpp"


class Inherited: public Base {
  /* intentionally left blank */
};  // class Inherited


Base* baseObj;            // Base is the object.
Inherited* inheritedObj;  // Base is inherited.

int main(int argc, char *argv[]){
  baseObj = new Base();
  inheritedObj = new Inherited();

  unsigned long int baseId = baseObj->getIdentifier();
  unsigned long int inheritedId = inheritedObj->getIdentifier();

  assert( baseId != 0 );
  assert( inheritedId != 0 );
  assert( inheritedId != baseId );

  return 0x0000;  // EXIT_SUCCESS;
}
