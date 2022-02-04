
#include <cassert>

#include "./src/test/core/list.hpp"
#include "./src/test/core/dict.hpp"


int main(int argc, char* argv[]) {

  assert( ListEntryTest::setValue_canStorePrimitiveTypes );
  assert( ListEntryTest::setValue_canStoreComplexTypes );
  assert( ListEntryTest::setNext_canStoreANewEntryInstance );
  assert( ListEntryTest::setPrev_canStoreANewEntryInstance );

  assert( ListTest::getLength_returnsTheCorrectLength() );
  assert( ListTest::set_insertsANewEntryAtTheGivenIndex() );
  assert( ListTest::set_insertsNullValuesPrecedingNewEntries() );
  assert( ListTest::push_insertsANewEntryAtTheEndOfTheList() );
  assert( ListTest::unshift_insertsANewEntryAtTheBeginningOfTheList() );
  assert( ListTest::fill_fillsTheExpectedAmountOfEntries() );
  assert( ListTest::fill_fillsTheWholeListOfNoIndicesAreGiven() );

}
