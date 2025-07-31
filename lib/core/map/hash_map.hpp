
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

  #define HASHMAP_ARRAY_LEN     128
  #define HASHMAP_LISTLEN_MAX   192

  #define MAX_HASHCODE_KEY_LEN    8


  template <class class_type>
  class HashMap: public Map<class_type> {

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

        //list->unshift(newEntry);  // LinkedList, BinaryTreeList
        list->push(newEntry);   // LinkedList, FixedTreeList, ArrayList

        this->data->set(aryIdx, list);

        uint32_t innerLoopLen = list->getLength();

        if (innerLoopLen >= HASHMAP_LISTLEN_MAX) {
          uint32_t newLen = this->data->getLength() + HASHMAP_ARRAY_LEN;

          this->rebase(newLen);
        }

      }

      void rebase(uint32_t newLen) {
        //ArrayList<LinkedList<HashMapNode<class_type>*>*>* oldData = this->data;
        //ArrayList<LinkedList<HashMapNode<class_type>*>*>* newData = new ArrayList<LinkedList<HashMapNode<class_type>*>*>();
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

          delete list;
        }

        delete oldData;
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
        LinkedList<const char*>* outp = new LinkedList<const char*>();
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

        if (func != NULL) {
          outp->sort(func);
        }

        return outp;
      }

      LinkedList<class_type>* getValues(int32_t(*func)(class_type, class_type)=NULL) {
        LinkedList<class_type>* outp = new LinkedList<class_type>();
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

        if (func != NULL) {
          outp->sort(func);
        }

        return outp;
      }

  };

#endif
