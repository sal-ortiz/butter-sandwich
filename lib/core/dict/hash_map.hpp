
#ifndef _HASHMAP_HPP

  #define _HASHMAP_HPP

  #include <string.h>
  #include <stdint.h>

  #include "./../list.hpp"
  #include "./../list/fixed_tree_list.hpp"
  #include "./hash_map/node.hpp"

  #define HASHMAP_ARRAY_LEN     128
  #define HASHMAP_LISTLEN_MAX   128

  #define MAX_HASHCODE_KEY_LEN    8

  #define REALLOC_BUFFER_SCALE  2


  template <class class_type>
  class HashMap {

    private:

      FixedTreeList<FixedTreeList<HashMapNode<class_type>*>*>* data;

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
        uint32_t aryIdx = HashMap::hashCode(key) % this->data->getLength();

        FixedTreeList<HashMapNode<class_type>*>* list = this->data->get(aryIdx);

        uint32_t listLen = list->getLength();

        HashMapNode<class_type>* entry;

        for (uint32_t idx = 0; idx < listLen; idx++) {
          entry = list->get(idx);

          if (entry == NULL) {
            break;
          }

          if (!strcmp(entry->key, key)) {
            return entry;
          }

        }

        return NULL;
      }

      void setEntry(const char* key, class_type value) {
        uint32_t aryIdx = HashMap::hashCode(key) % this->data->getLength();

        FixedTreeList<HashMapNode<class_type>*>* list = this->data->get(aryIdx);

        if (list == NULL) {
          list = new FixedTreeList<HashMapNode<class_type>*>();

          this->data->set(aryIdx, list);
        }

        HashMapNode<class_type>* entry;
        uint32_t listLen = list->getLength();

        for (uint32_t idx = 0; idx < listLen; idx++) {
          entry = list->get(idx);

          if (entry != NULL && strcmp(entry->key, key) == 0) {
            entry->value = value;

            return;
          }

        }

        HashMapNode<class_type>* newEntry = new HashMapNode<class_type>{};

        newEntry->key = key;
        newEntry->value = value;

        list->unshift(newEntry);  // FixedTreeList, FixedTreeList, BinaryTreeListi
        //list->push(newEntry);   // FixedTreeList, BinaryTreeList, ArrayList

        this->data->set(aryIdx, list);

        uint32_t innerLoopLen = list->getLength();

        if (innerLoopLen > HASHMAP_LISTLEN_MAX) {
          uint32_t newLen = this->data->getLength() + HASHMAP_ARRAY_LEN;

          this->rebase(newLen);
        }

      }


      public: // only for testing purposes

      void rebase(uint32_t newLen) {
        FixedTreeList<FixedTreeList<HashMapNode<class_type>*>*>* oldData = this->data;
        FixedTreeList<FixedTreeList<HashMapNode<class_type>*>*>* newData = new FixedTreeList<FixedTreeList<HashMapNode<class_type>*>*>();

        newData->set(newLen, NULL);

        this->data = newData;

        uint32_t oldDataLen = oldData->getLength();

        for (uint32_t idx = 0; idx < oldDataLen; idx++) {
          FixedTreeList<HashMapNode<class_type>*>* list = oldData->get(idx);

          if (list == NULL) {
            continue;
          }

          uint32_t listLen = list->getLength();

          for (uint32_t listIdx = 0; listIdx < listLen; listIdx++) {
            HashMapNode<class_type>* entry = list->get(listIdx);

            if (entry == NULL) {
              continue;
            }

            this->setEntry(entry->key, entry->value);
          }

        }

        delete oldData;
      }

      //void deleteEntry(const char* key) {
      //  uint32_t aryIdx = HashMap::hashCode(key) % this->listArrayLen;
      //
      //  FixedTreeList<HashMapNode<class_type>> list = data[aryIdx];
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


    //public:

      HashMap() {
        this->data = new FixedTreeList<FixedTreeList<HashMapNode<class_type>*>*>();

        this->data->set(HASHMAP_ARRAY_LEN - 1, NULL);

      }

      ~HashMap() {
        uint32_t aryLen = this->data->getLength();

        for (uint32_t idx = 0; idx < aryLen; idx++) {
          FixedTreeList<HashMapNode<class_type>*>* list = this->data->get(idx);

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

        delete this->data;
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

        List<const char*>* outp = new List<const char*>();
        //uint32_t aryLen = this->listArrayLen;
        uint32_t aryLen = this->data->getLength();;

        for (uint32_t aryIdx = 0; aryIdx < aryLen; aryIdx++) {
          //FixedTreeList<HashMapNode<class_type>*>* list = data[aryIdx];
          FixedTreeList<HashMapNode<class_type>*>* list = data->get(aryIdx);

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
        //uint32_t aryLen = this->listArrayLen;
        uint32_t aryLen = this->data->getLength();;

        for (uint32_t aryIdx = 0; aryIdx < aryLen; aryIdx++) {
          //FixedTreeList<HashMapNode<class_type>*>* list = data[aryIdx];
          FixedTreeList<HashMapNode<class_type>*>* list = data->get(aryIdx);

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
