
#ifndef _DICT_ENTRY_HPP

  #define _DICT_ENTRY_HPP


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
        this->key = key;
        this->value = value;
      }

      const char* getKey() {
        return this->key;
      }

      void setKey(const char* newKey) {
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
