
unsigned long int NULL = 0;

#include "../../lib/core/list.hpp"


class ListEntryTest {

  public:

    static bool setValue_canStorePrimitiveTypes() {
      ListEntry<unsigned long int>* instance = new ListEntry<unsigned long int>();

      instance->setValue(1234);

      return instance->getValue() == 1234;
    }

    static bool setValue_canStoreComplexTypes() {
      struct ComplexType {
        unsigned long int value;
      };

      ListEntry<ComplexType>* instance = new ListEntry<ComplexType>();
      ComplexType complexValue = { 1234 };

      instance->setValue(complexValue);

      return instance->getValue().value == complexValue.value;
    }

    static bool setNext_canStoreANewEntryInstance() {
      ListEntry<unsigned long int>* instance = new ListEntry<unsigned long int>();
      ListEntry<unsigned long int>* next = new ListEntry<unsigned long int>();

      next->setValue(1234);
      instance->setNext(next);

      return instance->getNext()->getValue() == 1234;
    }

    static bool setPrev_canStoreANewEntryInstance() {
      ListEntry<unsigned long int>* instance = new ListEntry<unsigned long int>();
      ListEntry<unsigned long int>* prev = new ListEntry<unsigned long int>();

      unsigned long int value = 65536;

      prev->setValue(value);
      instance->setPrev(prev);

      return instance->getPrev()->getValue() == value;
    }

};


class ListTest {

  public:

    static bool getLength_returnsTheCorrectLength() {
      List<unsigned long int>* instance = new List<unsigned long int>();

      instance->push(1234);
      instance->push(1234);

      return instance->getLength() == 2;
    }

    static bool set_insertsANewEntryAtTheGivenIndex() {
      List<unsigned long int>* instance = new List<unsigned long int>();

      instance->set(10, 1234);

      return instance->get(10) == 1234;
    }

    static bool set_insertsNullValuesPrecedingNewEntries() {
      List<unsigned long int>* instance = new List<unsigned long int>();

      instance->set(5, 1234);
      instance->set(3, 4321);

      return true &&
        instance->get(0) == NULL &&
        instance->get(1) == NULL &&
        instance->get(2) == NULL &&
        instance->get(3) == 4321 &&
        instance->get(4) == NULL &&
        instance->get(5) == 1234;
    }

    static bool push_insertsANewEntryAtTheEndOfTheList() {
      List<unsigned long int>* instance = new List<unsigned long int>();

      instance->set(5, 4321);
      instance->push(1234);

      return (instance->getLength() == 7) && (instance->get(6) == 1234);
    }

    static bool unshift_insertsANewEntryAtTheBeginningOfTheList() {
      List<unsigned long int>* instance = new List<unsigned long int>();

      instance->set(5, 4321);
      instance->unshift(1234);

      return (instance->getLength() == 7) && (instance->get(0) == 1234);
    }

    static bool pop_removesAValueFromTheEndOfTheList() {
      List<unsigned long int>* instance = new List<unsigned long int>();

      instance->set(0, 4321);
      instance->set(5, 1234);
      unsigned long int value = instance->pop();

      return (instance->getLength() == 5) && (value == 1234);
    }

    static bool shift_removesAValueFromTheBeginningOfTheList() {
      List<unsigned long int>* instance = new List<unsigned long int>();

      instance->set(0, 1234);
      instance->set(5, 4321);
      unsigned long int value = instance->shift();

      return (instance->getLength() == 5) && (value == 1234);
    }

    static bool fill_fillsTheExpectedAmountOfEntries() {
      List<unsigned long int>* instance = new List<unsigned long int>();

      instance->fill(1234, 5, 1);

      return true &&
        instance->get(0) == NULL &&
        instance->get(1) == 1234 &&
        instance->get(2) == 1234 &&
        instance->get(3) == 1234 &&
        instance->get(4) == 1234 &&
        instance->get(5) == 1234;
    }

    static bool fill_fillsTheWholeListOfNoIndicesAreGiven() {
      List<unsigned long int>* instance = new List<unsigned long int>();

      instance->set(5, 4321);
      instance->fill(1234);

      return true &&
        instance->get(0) == 1234 &&
        instance->get(1) == 1234 &&
        instance->get(2) == 1234 &&
        instance->get(3) == 1234 &&
        instance->get(4) == 1234 &&
        instance->get(5) == 1234;
    }

};
