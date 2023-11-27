
#ifndef _DICT_HPP

  #define _DICT_HPP

  #include <string.h>

  #include "./list.hpp"
  #include "./dict/entry.hpp"

  #define DICT_LIST_ARRAY_LEN   64


  template <class class_type>
  class Dict {

    private:

      List<DictEntry<class_type>*>* data[DICT_LIST_ARRAY_LEN];

      unsigned long int hashCode(const char* key) {
        unsigned long int outpValue = 1;
        unsigned int keyLen = strlen(key);

        for (unsigned int keyIdx = 0; keyIdx < keyLen; keyIdx++) {
          unsigned char curChar = (unsigned char)key[keyIdx];

          outpValue *= curChar;
        }

        return outpValue;
      }

      DictEntry<class_type>* getEntry(const char* key) {
        unsigned long int aryIdx = this->hashCode(key) % DICT_LIST_ARRAY_LEN;

        List<DictEntry<class_type>*>* list = this->data[aryIdx];
        DictEntry<class_type>* entry;

        unsigned long int listLen = list->getLength();

        bool found = false;

        for (unsigned long int idx = 0; idx < listLen; idx++) {
          entry = list->get(idx);
          unsigned int cmp = strcmp(entry->getKey(), key);

          if (cmp == 0) {
            found = true;

            break;
          }

        }

        if (!found) {
          return NULL;
        } else {
          return entry;
        }

      }

      void setEntry(const char* key, class_type value) {
        unsigned long int aryIdx = this->hashCode(key) % DICT_LIST_ARRAY_LEN;

        List<DictEntry<class_type>*>* list = this->data[aryIdx];
        DictEntry<class_type>* entry;


        unsigned long int listLen = list->getLength();

        bool found = false;

        for (unsigned long int idx = 0; idx < listLen; idx++) {
          // HACKY!!! write a more efficient way to do this.
          entry = list->get(idx);

          int cmp = strcmp(entry->getKey(), key);

          if (cmp == 0) {
            found = true;

            break;
          }

        }

        if (found) {
          entry->setValue(value);

        } else {
          DictEntry<class_type>* newEntry = new DictEntry<class_type>(key, value);

          list->unshift(newEntry);
          //list->push(newEntry);

          this->data[aryIdx] = list;
        }

      }

      //void deleteEntry(const char* key) {
      //  unsigned long int aryIdx = this->hashCode(key) % DICT_LIST_ARRAY_LEN;
      //
      //  List<DictEntry<class_type>> list = data[aryIdx];
      //  DictEntry<class_type> entry;
      //
      //  unsigned long int listLen = list.getLength();
      //
      //  bool found = false;
      //
      //  for (unsigned long int idx = 0; idx < listLen; idx++) {
      //    entry = list.get(idx);
      //
      //    int cmp = strcmp(entry.getKey(), key);
      //
      //    if (cmp == 0) {
      //      found = true;
      //
      //      list.remove(idx);
      //
      //      break;
      //    }
      //
      //  }
      //
      //  //if (!found) {
      //  //  throw (void*)NULL;
      //  //}
      //
      //}


    public:

      Dict() {

        for (unsigned long int idx = 0; idx < DICT_LIST_ARRAY_LEN; idx++) {
          this->data[idx] = new List<DictEntry<class_type>*>();
        }

      }

      ~Dict() {

        for (long unsigned int idx = 0; idx < DICT_LIST_ARRAY_LEN; idx++) {
          List<DictEntry<class_type>*>* list = this->data[idx];

          unsigned long int listLen = list->getLength();

          for (unsigned long int listIdx = 0; listIdx < listLen; listIdx++) {
            DictEntry<class_type>* entry = list->get(listIdx);

            delete entry;
          }

          delete list;
        }

      }

      class_type get(const char* key) {
        DictEntry<class_type>* entry = this->getEntry(key);

        if (entry == NULL) {
          return NULL;
        }

        return entry->getValue();
      }

      void set(const char* key, class_type value) {
        this->setEntry(key, value);
      }

      //void remove(const char* key) {
      //  this->deleteEntry(key);
      //}

      List<char*>* getKeys() {
        // TODO: It might be faster/efficient to merge the various lists
        //       contained in data instead of iterating through each one.

        List<char*>* outp = new List<char*>();

        for (unsigned long int aryIdx = 0; aryIdx < DICT_LIST_ARRAY_LEN; aryIdx++) {
          List<DictEntry<class_type>>* list = data[aryIdx];

          unsigned long int listLen = list->getLength();

          for (unsigned long int listIdx = 0; listIdx < listLen; listIdx++) {
            DictEntry<class_type>* entry = list->get(listIdx);

            char* key = entry->getKey();

            outp->push(key);
          }

        }

        return outp;
      }

      List<class_type>* getValues() {
        // TODO: It might be faster/efficient to merge the various lists
        //       contained in data instead of iterating through each one.

        List<class_type>* outp = new List<class_type>();

        for (unsigned long int aryIdx = 0; aryIdx < DICT_LIST_ARRAY_LEN; aryIdx++) {
          List<DictEntry<class_type>*>* list = data[aryIdx];

          unsigned long int listLen = list->getLength();

          for (unsigned long int listIdx = 0; listIdx < listLen; listIdx++) {
            DictEntry<class_type>* entry = list->get(listIdx);

            class_type value = entry->getValue();

            outp->push(value);
          }

        }

        return outp;
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
