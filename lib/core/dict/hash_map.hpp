
#ifndef _HASHMAP_HPP

  #define _HASHMAP_HPP

  #include <string.h>
  #include <stdint.h>

  #include "./../list.hpp"
  #include "./../list/linked_list.hpp"
  #include "./hash_map/node.hpp"

  #define HASHMAP_LIST_ARYLEN   128
  #define HASHMAP_LISTLEN_MAX   512

  #define MAX_HASHCODE_KEY_LEN    8

  template <class class_type>
  class HashMap {

    private:

      uint32_t listArrayLen;

      LinkedList<HashMapNode<class_type>*>** data;

      static uint32_t hashCode(const char* key) {
        uint32_t outpValue = 7;
        uint8_t curChar = (uint8_t)key[0];

        for (uint32_t keyIdx = 1; curChar != 0; keyIdx++) {

          outpValue *= curChar;

          if (keyIdx == MAX_HASHCODE_KEY_LEN) {
            break;
          }

          curChar = (uint8_t)key[keyIdx];
        }

        return outpValue;
      }

      HashMapNode<class_type>* getEntry(const char* key) {
        uint32_t aryIdx = HashMap::hashCode(key) % this->listArrayLen;

        LinkedList<HashMapNode<class_type>*>* list = this->data[aryIdx];

        uint32_t listLen = list->getLength();

        HashMapNode<class_type>* entry;

        for (uint32_t idx = 0; idx < listLen; idx++) {
          entry = list->get(idx);

          if (!strcmp(entry->key, key)) {
            return entry;
          }

        }

        return NULL;
      }

      void setEntry(const char* key, class_type value) {
        uint32_t aryIdx = HashMap::hashCode(key) % this->listArrayLen;

        LinkedList<HashMapNode<class_type>*>* list = this->data[aryIdx];
        HashMapNode<class_type>* entry;

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

        list->unshift(newEntry);  // LinkedList, FixedTreeList, BinaryTreeListi
        //list->push(newEntry);   // FixedTreeList, BinaryTreeList, ArrayList

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
        uint32_t newArySize = newAryLen * sizeof(LinkedList<HashMapNode<class_type>*>*);

        LinkedList<HashMapNode<class_type>*>** newAry = (LinkedList<HashMapNode<class_type>*>**)malloc(newArySize);

        for (uint32_t newAryIdx = 0; newAryIdx < newAryLen; newAryIdx++) {
          newAry[newAryIdx] = new LinkedList<HashMapNode<class_type>*>();
        }

        for (uint32_t aryIdx = 0; aryIdx < aryLen; aryIdx++) {
          LinkedList<HashMapNode<class_type>*>* curLinkedList = this->data[aryIdx];

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
      //  LinkedList<HashMapNode<class_type>> list = data[aryIdx];
      //  HashMapNode<class_type> entry;
      //
      //  uint32_t listLen = list.getLength();
      //
      //  bool found = false;
      //
      //  for (uint32_t idx = 0; idx < listLen; idx++) {
      //    entry = list.get(idx);
      //
      //    if (!strcmp(entry.key, key) == 0) {
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
        this->listArrayLen = HASHMAP_LIST_ARYLEN;

        uint32_t arySize = this->listArrayLen * sizeof(LinkedList<HashMapNode<class_type>*>*);

        this->data = (LinkedList<HashMapNode<class_type>*>**)malloc(arySize);

        for (uint32_t aryIdx = 0; aryIdx < this->listArrayLen; aryIdx++) {
          this->data[aryIdx] = new LinkedList<HashMapNode<class_type>*>();
        }

      }

      ~HashMap() {
        uint32_t aryLen = this->listArrayLen;

        for (uint32_t idx = 0; idx < aryLen; idx++) {
          LinkedList<HashMapNode<class_type>*>* list = this->data[idx];

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

        free(this->data);
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

      LinkedList<const char*>* getKeys() {
        // TODO: It might be faster/efficient to merge the various lists
        //       contained in data instead of iterating through each one.

        LinkedList<const char*>* outp = new LinkedList<const char*>();
        uint32_t aryLen = this->listArrayLen;

        for (uint32_t aryIdx = 0; aryIdx < aryLen; aryIdx++) {
          LinkedList<HashMapNode<class_type>*>* list = data[aryIdx];

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

        List<class_type>* outp = new List<class_type>();
        uint32_t aryLen = this->listArrayLen;

        for (uint32_t aryIdx = 0; aryIdx < aryLen; aryIdx++) {
          LinkedList<HashMapNode<class_type>*>* list = data[aryIdx];

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
