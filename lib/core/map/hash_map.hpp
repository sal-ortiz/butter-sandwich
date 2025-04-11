
#ifndef _HASHMAP_HPP

  #define _HASHMAP_HPP

  #include <string.h>
  #include <stdint.h>

  #include "./map.hpp"
  #include "../list/list.hpp"
  #include "../list/fixed_tree_list.hpp"
  #include "./node/hash_map_node.hpp"

  #define HASHMAP_ARRAY_LEN     128
  #define HASHMAP_LISTLEN_MAX   192

  #define MAX_HASHCODE_KEY_LEN    8


  template <class class_type>
  class HashMap: public Map<class_type> {

    private:

      FixedTreeList<LinkedList<HashMapNode<class_type>*>*>* data;

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

        LinkedList<HashMapNode<class_type>*>* list = this->data->get(aryIdx);

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

        LinkedList<HashMapNode<class_type>*>* list = this->data->get(aryIdx);

        if (list == NULL) {
          list = new LinkedList<HashMapNode<class_type>*>();

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

        list->unshift(newEntry);  // LinkedList, BinaryTreeList
        //list->push(newEntry);   // FixedTreeList, BinaryTreeList, ArrayList

        this->data->set(aryIdx, list);

        uint32_t innerLoopLen = list->getLength();

        if (innerLoopLen > HASHMAP_LISTLEN_MAX) {
          uint32_t newLen = this->data->getLength() + HASHMAP_ARRAY_LEN;

          printf("REBASING to %d / %d\n", list->getLength(), this->data->getLength());

          this->rebase(newLen);
        }

      }

      void rebase(uint32_t newLen) {
        FixedTreeList<LinkedList<HashMapNode<class_type>*>*>* oldData = this->data;
        FixedTreeList<LinkedList<HashMapNode<class_type>*>*>* newData = new FixedTreeList<LinkedList<HashMapNode<class_type>*>*>();

        newData->set(newLen, NULL);

        this->data = newData;

        uint32_t oldDataLen = oldData->getLength();

        for (uint32_t idx = 0; idx < oldDataLen; idx++) {
          LinkedList<HashMapNode<class_type>*>* list = oldData->get(idx);

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

            delete entry;
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


    public:

      HashMap() {
        this->data = new FixedTreeList<LinkedList<HashMapNode<class_type>*>*>();

        this->data->set(HASHMAP_ARRAY_LEN - 1, NULL);

      }

      ~HashMap() {
        uint32_t aryLen = this->data->getLength();

        for (uint32_t idx = 0; idx < aryLen; idx++) {
          LinkedList<HashMapNode<class_type>*>* list = this->data->get(idx);

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
        List<const char*>* outp = new List<const char*>();
        uint32_t aryLen = this->data->getLength();;

        for (uint32_t aryIdx = 0; aryIdx < aryLen; aryIdx++) {
          LinkedList<HashMapNode<class_type>*>* list = data->get(aryIdx);

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
        List<class_type>* outp = new List<class_type>();
        uint32_t aryLen = this->data->getLength();;

        for (uint32_t aryIdx = 0; aryIdx < aryLen; aryIdx++) {
          LinkedList<HashMapNode<class_type>*>* list = data->get(aryIdx);

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
