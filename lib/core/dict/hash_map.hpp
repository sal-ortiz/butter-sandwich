
#ifndef _HASHMAP_HPP

  #define _HASHMAP_HPP

  #include <string.h>
  #include <stdint.h>

  #include "./../list.hpp"
  #include "./hash_map/node.hpp"

  #define HASHMAP_LIST_ARYLEN   64
  #define HASHMAP_LISTLEN_MAX   36

  template <class class_type>
  class HashMap {


    private:

      uint32_t listArrayLen = HASHMAP_LIST_ARYLEN;

      // TODO: init'd and sized dynamically in the code, not here.
      List<HashMapNode<class_type>*>** data;

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
        uint32_t aryIdx = HashMap::hashCode(key) % this->listArrayLen;

        List<HashMapNode<class_type>*>* list = this->data[aryIdx];
        HashMapNode<class_type>* entry;

        uint32_t listLen = list->getLength();

        bool found = false;

        for (uint32_t idx = 0; idx < listLen; idx++) {
          entry = list->get(idx);
          int32_t cmp = strcmp(entry->key, key);

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
        uint32_t aryIdx = HashMap::hashCode(key) % this->listArrayLen;

        List<HashMapNode<class_type>*>* list = this->data[aryIdx];
        HashMapNode<class_type>* entry;

        if (list == NULL) {
          this->data[aryIdx] = new List<HashMapNode<class_type>*>();

          list = this->data[aryIdx];
        }


        uint32_t listLen = list->getLength();

        bool found = false;

        for (uint32_t idx = 0; idx < listLen; idx++) {
          // HACKY!!! write a more efficient way to do this.
          entry = list->get(idx);

          if (entry != NULL && !strcmp(entry->key, key)) {
            entry->value = value;

            return;
          }

        }

        HashMapNode<class_type>* newEntry = new HashMapNode<class_type>{};

        newEntry->key = key;
        newEntry->value = value;

        list->unshift(newEntry);

        this->data[aryIdx] = list;

        if (this->data[aryIdx]->getLength() > HASHMAP_LISTLEN_MAX) {
          uint32_t newLen = this->listArrayLen * 2;

          //printf("\nREBASING: %s", key);

          //this->rebase(newLen);
        }

      }

      void rebase(uint32_t newLen) {
        uint32_t aryLen = this->listArrayLen;
        uint32_t newAryLen = newLen;  // assumes new length > old length
        uint32_t newArySize = newAryLen * sizeof(List<HashMapNode<class_type>*>*);

        List<HashMapNode<class_type>*>** newAry = (List<HashMapNode<class_type>*>**)malloc(newArySize);

        for (uint32_t newAryIdx = 0; newAryIdx < newAryLen; newAryIdx++) {
          newAry[newAryIdx] = new List<HashMapNode<class_type>*>();
        }

        for (uint32_t aryIdx = 0; aryIdx < aryLen; aryIdx++) {
          List<HashMapNode<class_type>*>* curList = this->data[aryIdx];

          uint32_t curListLen = curList->getLength();

          for (uint32_t curListIdx = 0; curListIdx < curListLen; curListIdx++) {
            HashMapNode<class_type>* curEntry = curList->get(curListIdx);

            const char* curKey = curEntry->key;

            uint32_t newAryIdx = HashMap::hashCode(curKey) % newAryLen;

            newAry[newAryIdx]->unshift(curEntry);
          }

          delete curList;
        }

        this->listArrayLen = newAryLen;

        free(this->data);

        this->data = newAry;
      }

      //void deleteEntry(const char* key) {
      //  uint32_t aryIdx = HashMap::hashCode(key) % this->listArrayLen;
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
      //    int32_t cmp = strcmp(entry.key, key);
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
        uint32_t aryLen = this->listArrayLen;
        uint32_t arySize = aryLen * sizeof(List<HashMapNode<class_type>*>*);

        this->data = (List<HashMapNode<class_type>*>**)malloc(arySize);

        for (uint32_t idx = 0; idx < aryLen; idx++) {
          this->data[idx] = new List<HashMapNode<class_type>*>{};
        }

      }

      ~HashMap() {
        uint32_t aryLen = this->listArrayLen;

        for (uint32_t idx = 0; idx < aryLen; idx++) {
          List<HashMapNode<class_type>*>* list = this->data[idx];

          if (list == NULL) {
            continue;
          }

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

        return entry->value;
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

        List<const char*>* outp = new List<const char*>{};
        uint32_t aryLen = this->listArrayLen;

        for (uint32_t aryIdx = 0; aryIdx < aryLen; aryIdx++) {
          List<HashMapNode<class_type>*>* list = data[aryIdx];

          if (list == NULL) {
            continue;
          }

          uint32_t listLen = list->getLength();

          for (uint32_t listIdx = 0; listIdx < listLen; listIdx++) {
            HashMapNode<class_type>* entry = list->get(listIdx);

            const char* key = entry->key;

            //if (key != NULL) {
              outp->push(key);
            //}

          }

        }

        return outp;
      }

      List<class_type>* getValues() {
        // TODO: It might be faster/efficient to merge the various lists
        //       contained in data instead of iterating through each one.

        List<class_type>* outp = new List<class_type>{};
        uint32_t aryLen = this->listArrayLen;

        for (uint32_t aryIdx = 0; aryIdx < aryLen; aryIdx++) {
          List<HashMapNode<class_type>*>* list = data[aryIdx];

          if (list == NULL) {
            continue;
          }

          uint32_t listLen = list->getLength();

          for (uint32_t listIdx = 0; listIdx < listLen; listIdx++) {
            HashMapNode<class_type>* entry = list->get(listIdx);

            class_type value = entry->value;

            outp->push(value);
          }

        }

        return outp;
      }

  };

#endif
