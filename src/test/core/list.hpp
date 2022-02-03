
unsigned long int NULL = 0;

#include "../../lib/core/list.hpp"


class ListEntryTest {


  public:

    static bool setValue_canStorePrimitiveTypes() {
      ListEntry<unsigned long int>* instance = new ListEntry<unsigned long int>();
      unsigned long int value = 65536;

      instance->setValue(value);

      return instance->getValue() == value;
    }

    static bool setValue_canStoreComplexTypes() {
      struct ComplexType {
        unsigned long int value;
      };

      ListEntry<ComplexType>* instance = new ListEntry<ComplexType>();
      ComplexType complexValue = { 65535 };

      instance->setValue(complexValue);

      return instance->getValue().value == complexValue.value;
    }

    static bool setNext_canStoreANewEntryInstance() {
      ListEntry<unsigned long int>* instance = new ListEntry<unsigned long int>();
      ListEntry<unsigned long int>* next = new ListEntry<unsigned long int>();

      unsigned long int value = 65536;

      next->setValue(value);
      instance->setNext(next);

      return instance->getNext()->getValue() == value;
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

};
