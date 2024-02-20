
#ifndef _HASHMAP_HPP

  #define _HASHMAP_HPP

  #include <string.h>
  #include <stdint.h>

  #include "./../list.hpp"
  #include "./hash_map/node.hpp"

  #define HASHMAP_LIST_ARRAY_LEN   64


  template <class class_type>
  class HashMap {

    private:

      List<HashMapNode<class_type>*>* data[HASHMAP_LIST_ARRAY_LEN];

      static uint32_t hashCode(const char* key) {
        uint32_t outpValue = 1;
        uint32_t keyLen = strlen(key);

        for (uint32_t keyIdx = 0; keyIdx < keyLen; keyIdx++) {
          uint8_t curChar = (uint8_t)key[keyIdx];

          outpValue *= curChar;
        }

        return outpValue;
      }

      HashMapNode<class_type>* getEntry(const char* key) {
        uint32_t aryIdx = HashMap::hashCode(key) % HASHMAP_LIST_ARRAY_LEN;

        List<HashMapNode<class_type>*>* list = this->data[aryIdx];
        HashMapNode<class_type>* entry;

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
        uint32_t aryIdx = HashMap::hashCode(key) % HASHMAP_LIST_ARRAY_LEN;

        List<HashMapNode<class_type>*>* list = this->data[aryIdx];
        HashMapNode<class_type>* entry;


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
          HashMapNode<class_type>* newEntry = new HashMapNode<class_type>(key, value);

          list->unshift(newEntry);
          //list->push(newEntry);

          this->data[aryIdx] = list;
        }

      }

      //void deleteEntry(const char* key) {
      //  uint32_t aryIdx = HashMap::hashCode(key) % HASHMAP_LIST_ARRAY_LEN;
      //
      //  List<HashMapNode<class_type>> list = data[aryIdx];
      //  HashMapNode<class_type> entry;
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

      HashMap() {

        for (uint32_t idx = 0; idx < HASHMAP_LIST_ARRAY_LEN; idx++) {
          this->data[idx] = new List<HashMapNode<class_type>*>();
        }

      }

      ~HashMap() {

        for (uint32_t idx = 0; idx < HASHMAP_LIST_ARRAY_LEN; idx++) {
          List<HashMapNode<class_type>*>* list = this->data[idx];

          uint32_t listLen = list->getLength();

          for (uint32_t listIdx = 0; listIdx < listLen; listIdx++) {
            HashMapNode<class_type>* entry = list->get(listIdx);

            delete entry;
          }

          delete list;
        }

      }

      class_type get(const char* key) {
        HashMapNode<class_type>* entry = this->getEntry(key);

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

      List<const char*>* getKeys() {
        // TODO: It might be faster/efficient to merge the various lists
        //       contained in data instead of iterating through each one.

        List<const char*>* outp = new List<const char*>();

        for (uint32_t aryIdx = 0; aryIdx < HASHMAP_LIST_ARRAY_LEN; aryIdx++) {
          List<HashMapNode<class_type>*>* list = data[aryIdx];

          uint32_t listLen = list->getLength();

          for (uint32_t listIdx = 0; listIdx < listLen; listIdx++) {
            HashMapNode<class_type>* entry = list->get(listIdx);

            const char* key = entry->getKey();

            outp->push(key);
          }

        }

        return outp;
      }

      List<class_type>* getValues() {
        // TODO: It might be faster/efficient to merge the various lists
        //       contained in data instead of iterating through each one.

        List<class_type>* outp = new List<class_type>();

        for (uint32_t aryIdx = 0; aryIdx < HASHMAP_LIST_ARRAY_LEN; aryIdx++) {
          List<HashMapNode<class_type>*>* list = data[aryIdx];

          uint32_t listLen = list->getLength();

          for (uint32_t listIdx = 0; listIdx < listLen; listIdx++) {
            HashMapNode<class_type>* entry = list->get(listIdx);

            class_type value = entry->getValue();

            outp->push(value);
          }

        }

        return outp;
      }

      bool has(const char* key) {
        return !!this->getEntry(key);
      }

  };

#endif
