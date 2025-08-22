
#ifndef _HASHMAP_HPP

  #define _HASHMAP_HPP

  #include <string.h>
  #include <stdint.h>
  #include <math.h>

  #include <core/map/map.hpp>
  #include <core/map/node/hash_map_node.hpp>
  #include <core/list/list.hpp>
  //#include <core/list/array_list.hpp>
  #include <core/list/fixed_tree_list.hpp>
  #include <core/list/linked_list.hpp>
  #include <tools/logger.hpp>

  #define HASHMAP_ARRAY_LEN     192
  #define HASHMAP_LISTLEN_MAX   128


  #define MAX_HASHCODE_KEY_LEN    10


  template <class class_type>
  class HashMap: public Map<class_type> {
    // an array of lists

    private:

      // TODO: We're probably better off using an ArrayList instead of a
      //       FixedTreeList here to facilitate random access. Unfortunately,
      //       there appears to be a bug in ArrayList that keeps triggering
      //       a "realloc(): invalid old size" error
      //ArrayList<LinkedList<HashMapNode<class_type>*>*>* data;
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

        for (uint32_t idx = 0; idx < listLen; idx++) {
          HashMapNode<class_type>* entry = list->get(idx);

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

        list->unshift(newEntry);  // LinkedList
        //list->push(newEntry);   // FixedTreeList, ArrayList, BinaryTreeList

        this->data->set(aryIdx, list);

        uint32_t innerLoopLen = list->getLength();

        if (innerLoopLen >= HASHMAP_LISTLEN_MAX) {
          uint32_t newLen = this->data->getLength() + HASHMAP_ARRAY_LEN;

          //Logger::info("rebasing HashMap list to %d entries from %d", newLen, this->data->getLength());
          this->rebase(newLen);
        }

      }

      void rebase(uint32_t newLen) {
        FixedTreeList<LinkedList<HashMapNode<class_type>*>*>* newData = new FixedTreeList<LinkedList<HashMapNode<class_type>*>*>();

        newData->set(newLen - 1, NULL);

        LinkedList<const char*>* keys = this->getKeys();
        uint32_t keysLen = keys->getLength();

        for (uint32_t idx = 0; idx < keysLen; idx++) {
          const char* key = keys->get(idx);
          uint32_t aryIdx = HashMap::hashCode(key) % newLen;

          LinkedList<HashMapNode<class_type>*>* list = newData->get(aryIdx);

          if (list == NULL) {
            list = new LinkedList<HashMapNode<class_type>*>();
          }

          HashMapNode<class_type>* node = this->getEntry(key);

          list->unshift(node);  // LinkedList
          //list->push(node);     // FixedTreeList, BinaryTreeList, ArrayList

          newData->set(aryIdx, list);
        }

        delete keys;
        delete this->data;

        this->data = newData;
      }

      void deleteEntry(const char* key) {
        uint32_t aryIdx = HashMap::hashCode(key) % this->data->getLength();

        LinkedList<HashMapNode<class_type>*>* list = this->data->get(aryIdx);

        uint32_t listLen = list->getLength();

        for (uint32_t idx = 0; idx < listLen; idx++) {
          HashMapNode<class_type>* el = list->get(idx);

          if (!strcmp(key, el->key)) {
            list->remove(idx);

            listLen--;
            delete el;

            //continue;
            break;
          }

        }

      }


    public:

      HashMap() {
        //this->data = new ArrayList<LinkedList<HashMapNode<class_type>*>*>();
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

            //delete entry->key;
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

      void remove(const char* key) {
        this->deleteEntry(key);
      }

      LinkedList<const char*>* getKeys(int32_t(*func)(const char*, const char*)=NULL) {
        LinkedList<const char*>* keys = new LinkedList<const char*>();
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

            keys->unshift(key);  // LinkedList
            //keys->push(key);     // FixedTreeList, BinaryTreeList, ArrayList
          }

        }

        if (func != NULL) {
          keys->sort(func);
        }

        return keys;
      }

      LinkedList<class_type>* getValues(int32_t(*func)(class_type, class_type)=NULL) {
        LinkedList<class_type>* vals = new LinkedList<class_type>();
        uint32_t aryLen = this->data->getLength();;

        for (uint32_t aryIdx = 0; aryIdx < aryLen; aryIdx++) {
          LinkedList<HashMapNode<class_type>*>* list = data->get(aryIdx);

          if (list == NULL) {
            continue;
          }

          uint32_t listLen = list->getLength();

          for (uint32_t listIdx = 0; listIdx < listLen; listIdx++) {
            HashMapNode<class_type>* entry = list->get(listIdx);

            class_type val = entry->value;

            vals->unshift(val);  // LinkedList
            //vals->push(val;     // FixedTreeList, BinaryTreeList, ArrayList
          }

        }

        if (func != NULL) {
          vals->sort(func);
        }

        return vals;
      }

  };

#endif
