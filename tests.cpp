
#include <cassert>

#include "./src/test/core/list.hpp"
#include "./src/test/core/dict.hpp"


int main(int argc, char* argv[]) {

  assert( ListEntryTest::setValue_canStorePrimitiveTypes );
  assert( ListEntryTest::setValue_canStoreComplexTypes );
  assert( ListEntryTest::setNext_canStoreANewEntryInstance );
  assert( ListEntryTest::setPrev_canStoreANewEntryInstance );



}
