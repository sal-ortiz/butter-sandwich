
#ifndef _DICT_ENTRY_HPP

  #define _DICT_ENTRY_HPP

  #include <string.h>


  template <class class_type>
  class DictEntry {

    private:

      const char* key;
      class_type value;


    public:

      DictEntry() {
        this->key = (const char*)NULL;
        this->value = (class_type)NULL;
      }

      DictEntry(const char* key, class_type value) {
        this->setKey(key);
        this->setValue(value);
      }

      ~DictEntry() {
        delete this->key;
      }

      const char* getKey() {
        return this->key;
      }

      void setKey(const char* key) {
        uint32_t keyLen = strlen(key);
        char* newKey = new char[keyLen + 1];

        strcpy(newKey, key);

        this->key = newKey;
      }

      class_type getValue() {
        return this->value;
      }

      void setValue(class_type newValue) {
        this->value = newValue;
      }

  };

#endif
