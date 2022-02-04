
#include <string.h>
#include "../../lib/core/dict.hpp"


class DictEntryTest {

  public:

    static bool setKey_storesTheGivenKey() {
      DictEntry<unsigned long int>* instance = new DictEntry<unsigned long int>();

      instance->setKey("KEY");

      return strcmp(instance->getKey(), "KEY") == 0;
    }

    static bool setValue_canStorePrimitiveTypes() {
      DictEntry<unsigned long int>* instance = new DictEntry<unsigned long int>();

      instance->setValue(1234);

      return instance->getValue() == 1234;
    }

    static bool setValue_canStoreComplexTypes() {
      struct ComplexType {
        unsigned long int value;
      };

      DictEntry<ComplexType>* instance = new DictEntry<ComplexType>();

      ComplexType complexValue = { 1234 };

      instance->setValue(complexValue);

      return instance->getValue().value == 1234;
    }

};


class DictTest {

  public:

    static bool set_addsANewEntryAtTheGivenKey() {
      Dict<unsigned long int>* instance = new Dict<unsigned long int>();

      instance->set("KEY", 1234);

      return instance->get("KEY") == 1234;
    }

};
