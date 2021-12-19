


#ifndef _DICT_ENTRY_HPP

  #define _DICT_ENTRY_HPP

  #include "./list.hpp"
  #include <string.h>


  template <class class_type>
  class DictEntry {

    private:

      const char* key;
      class_type value;


    public:

      DictEntry() {
        //this->key = NULL;
        //this->value = NULL;
      }


      DictEntry(const char* key, class_type value) {
        this->key = key;
        this->value = value;
      }

      const char* getKey() {
        return this->key;
      }

      class_type getValue() {
        return this->value;
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

        for (unsigned long int idx = 0; idx < listLen; idx++) {
          entry = list.get(idx);
          unsigned int cmp = strcmp(entry.getKey(), key);


          if (cmp == 0) {
            break;
          }

        }

        return entry.getValue();
      }

      void set(const char* key, class_type value) {
        unsigned long int aryIdx = this->hashCode(key) % DICT_LIST_ARRAY_LEN;

        List<DictEntry<class_type>> list = data[aryIdx];
        DictEntry<class_type>* newEntry = new DictEntry<class_type>(key, value);

        list.unshift(*newEntry);
      }

  };

#endif
