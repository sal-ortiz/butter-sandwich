
#ifndef _DICT_ENTRY_HPP

  #define _DICT_ENTRY_HPP

  #include <string.h>
  #include <stddef.h>

  #include "./list.hpp" // https://gist.github.com/sal-ortiz/74a414860a7525f3cdce493d039c4d30


  template <class class_type>
  class DictEntry {

    private:

      const char* key;
      class_type value;


    public:

      DictEntry() {
        this->key = (const char*)NULL;
        //this->value = (class_type)NULL;
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


#ifndef _DICT_HPP

  #define _DICT_HPP

  #define DICT_LIST_ARRAY_LEN   256

  template <class class_type>
  class Dict {

    private:

      List<DictEntry<class_type>>* data;

      unsigned long int hashCode(const char* key) {
        unsigned long int outpValue = 1;
        unsigned int keyLen = strlen(key);

        for (unsigned int keyIdx = 0; keyIdx < keyLen; keyIdx++) {
          unsigned char curChar = (unsigned char)key[keyIdx];

          outpValue *= curChar;
        }

        return outpValue;
      }


    public:

      Dict() {
        this->data = new List<DictEntry<class_type>>[DICT_LIST_ARRAY_LEN];
      }

      class_type get(const char* key) {
        unsigned long int aryIdx = this->hashCode(key) % DICT_LIST_ARRAY_LEN;

        List<DictEntry<class_type>> list = this->data[aryIdx];
        DictEntry<class_type> entry;

        unsigned long int listLen = list.getLength();

        bool found = false;

        for (unsigned long int idx = 0; idx < listLen; idx++) {
          entry = list.get(idx);
          unsigned int cmp = strcmp(entry.getKey(), key);

          if (cmp == 0) {
            found = true;

            break;
          }

        }

        if (!found) {
          throw (void*)NULL;
        } else {
          return entry.getValue();
        }

      }

      void set(const char* key, class_type value) {
        unsigned long int aryIdx = this->hashCode(key) % DICT_LIST_ARRAY_LEN;

        List<DictEntry<class_type>> list = data[aryIdx];
        DictEntry<class_type>* newEntry = new DictEntry<class_type>(key, value);

        list.unshift(*newEntry);
      }

      bool has(const char* key) {

        try {
          this->get(key);
        } catch(...) {
          return false;
        }

        return true;
      }

  };

#endif
