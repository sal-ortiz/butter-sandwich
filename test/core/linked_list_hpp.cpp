
#include <assert.h>
#include "../../src/core/linked_list.hpp"


class FakeInt {  public:
  int val;

  FakeInt(int newVal = NULL) {
    val = newVal;
  }

  operator int() {
    return val;
  }

  int operator =(int newVal) {
    return val = newVal;
  }

};

LinkedList<FakeInt> llist;

int main(int argc, char *argv[]) {

/*
  llistPtr = new LinkedList<FakeInt>(
               new LinkedListEntry<FakeInt>(0x01, 0x01, NULL,
               new LinkedListEntry<FakeInt>(0x02, 0x02, NULL,
               new LinkedListEntry<FakeInt>(0x03, 0x03, NULL,
               new LinkedListEntry<FakeInt>(0x04, 0x04, NULL, NULL))))
             );


  printf("ary.length: %lx\n", llistPtr->length());

  printf("ary[%ld]: %lx\n", 0, (llistPtr->getByIndex(0))->getVal());
  printf("ary[%ld]: %lx\n", 1, (llistPtr->getByIndex(1))->getVal());
  printf("ary[%ld]: %lx\n", 2, (llistPtr->getByIndex(2))->getVal());
  printf("ary[%ld]: %lx\n", 3, (llistPtr->getByIndex(3))->getVal());
*/

  assert( llist.length() == 0 );

  // insert some values into the list.
  for(unsigned char index=0; ++index <= 10; index) {
    assert( llist.length() == index-1 );
    assert( (unsigned long int)(llist.push(index, *(new FakeInt(index)))) == index );
  };

  // test that the values are actually in the list.
  for(unsigned char index=0; ++index <= 10; index) {
    assert( (llist.getByIdentifier(index))->getIdentifier() == index );
    assert( (llist.getByIdentifier(index))->getVal() == index );
  };

  // pop the contents off and verify what we got.
  for(unsigned char index=10; index > 0; index--) {
    assert( llist.pop() == index );
    assert( llist.length() == index-1 );
  };

  //assert( llist.length() == 0 );
  return 0x0000;  // EXIT_SUCCESS;
}
