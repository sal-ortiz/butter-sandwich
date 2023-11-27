
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

      uint32_t hashCode(const char* key) {
        uint32_t outpValue = 1;
        uint32_t keyLen = strlen(key);

        for (uint32_t keyIdx = 0; keyIdx < keyLen; keyIdx++) {
          uint8_t curChar = (uint8_t)key[keyIdx];

          outpValue *= curChar;
        }

        return outpValue;
      }

      DictEntry<class_type>* getEntry(const char* key) {
        uint32_t aryIdx = this->hashCode(key) % DICT_LIST_ARRAY_LEN;

        List<DictEntry<class_type>*>* list = this->data[aryIdx];
        DictEntry<class_type>* entry;

        uint32_t listLen = list->getLength();

        bool found = false;

        for (uint32_t idx = 0; idx < listLen; idx++) {
          entry = list->get(idx);
          int32_t cmp = strcmp(entry->getKey(), key);

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
        uint32_t aryIdx = this->hashCode(key) % DICT_LIST_ARRAY_LEN;

        List<DictEntry<class_type>*>* list = this->data[aryIdx];
        DictEntry<class_type>* entry;


        uint32_t listLen = list->getLength();

        bool found = false;

        for (uint32_t idx = 0; idx < listLen; idx++) {
          // HACKY!!! write a more efficient way to do this.
          entry = list->get(idx);

          int32_t cmp = strcmp(entry->getKey(), key);

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
      //  uint32_t aryIdx = this->hashCode(key) % DICT_LIST_ARRAY_LEN;
      //
      //  List<DictEntry<class_type>> list = data[aryIdx];
      //  DictEntry<class_type> entry;
      //
      //  uint32_t listLen = list.getLength();
      //
      //  bool found = false;
      //
      //  for (uint32_t idx = 0; idx < listLen; idx++) {
      //    entry = list.get(idx);
      //
      //    int32_t cmp = strcmp(entry.getKey(), key);
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

        for (uint32_t idx = 0; idx < DICT_LIST_ARRAY_LEN; idx++) {
          this->data[idx] = new List<DictEntry<class_type>*>();
        }

      }

      ~Dict() {

        for (uint32_t idx = 0; idx < DICT_LIST_ARRAY_LEN; idx++) {
          List<DictEntry<class_type>*>* list = this->data[idx];

          uint32_t listLen = list->getLength();

          for (uint32_t listIdx = 0; listIdx < listLen; listIdx++) {
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

        for (uint32_t aryIdx = 0; aryIdx < DICT_LIST_ARRAY_LEN; aryIdx++) {
          List<DictEntry<class_type>>* list = data[aryIdx];

          uint32_t listLen = list->getLength();

          for (uint32_t listIdx = 0; listIdx < listLen; listIdx++) {
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

        for (uint32_t aryIdx = 0; aryIdx < DICT_LIST_ARRAY_LEN; aryIdx++) {
          List<DictEntry<class_type>*>* list = data[aryIdx];

          uint32_t listLen = list->getLength();

          for (uint32_t listIdx = 0; listIdx < listLen; listIdx++) {
            DictEntry<class_type>* entry = list->get(listIdx);

            class_type value = entry->getValue();

            outp->push(value);
          }

        }

        return outp;
      }

      bool has(const char* key) {
        return !!this->get(key);
      }

  };

#endif
