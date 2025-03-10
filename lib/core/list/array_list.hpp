
#ifndef _ARRAY_LIST_HPP

  #define _ARRAY_LIST_HPP

  #include <stdint.h>
  #include <stdio.h>
  #include <math.h>

  #include "./array_list/node.hpp"

  #define _ARRAY_LIST_ALLOC_INCREMENT   64


  template <class class_type>
  class ArrayList {

    private:

      ArrayListNode<class_type>** array;

      uint32_t arraySize;
      uint32_t length;

      void allocateArray(uint32_t newLen) {
        uint32_t newSize = newLen * sizeof(ArrayListNode<class_type>*);

        this->array = (ArrayListNode<class_type>**)realloc(this->array, newSize);
        this->arraySize = newSize;
      }

      ArrayListNode<class_type>* getEntry(uint32_t targIndex) {

        if (targIndex >= this->length) {
          return NULL;
        }

        return this->array[targIndex];
      }

      void setEntry(uint32_t targIndex, class_type value) {
        uint32_t arySize = this->arraySize;
        uint32_t aryLen = this->arraySize / sizeof(ArrayListNode<class_type>*);

        if ((targIndex * sizeof(ArrayListNode<class_type>*)) > arySize) {
          this->allocateArray(targIndex + _ARRAY_LIST_ALLOC_INCREMENT);
        }

        ArrayListNode<class_type>* curNode = this->array[targIndex];

        if (curNode == NULL) {
          curNode = new ArrayListNode<class_type>();
        }

        curNode->value = value;

        this->array[targIndex] = curNode;

        if (targIndex >= this->length) {
          this->length = targIndex + 1;
        }

      }

      void insertEntry(uint32_t targIndex, class_type value) {
        ArrayListNode<class_type>* curNode;

        for (uint32_t idx = this->length - 1; idx > targIndex; idx--) {
          curNode = this->getEntry(idx);

          if (curNode) {
            this->setEntry(idx + 1, curNode->value);
          } else {
            this->setEntry(idx + 1, NULL);
          }

        }

        ArrayListNode<class_type>* lastNode = this->getEntry(targIndex);

        this->setEntry(targIndex + 1, lastNode->value);
        this->setEntry(targIndex, value);
      }

      void deleteEntry(uint32_t targIndex) {

        if (targIndex >= this->length) {
          return;
        }

        for (uint32_t idx = targIndex; idx < this->length; idx++) {
          ArrayListNode<class_type>* curNode = this->getEntry(idx + 1);

          if (curNode != NULL) {
            this->setEntry(idx, curNode->value);
          }

        }

        this->setEntry(this->length - 1, NULL);
        this->length--;
      }


    public:

      ArrayList() {
        this->length = 0;

        this->array = NULL;
        this->allocateArray(_ARRAY_LIST_ALLOC_INCREMENT);
      }

      ~ArrayList() {
        free(this->array);
      }

      uint32_t getLength() {
        return this->length;
      }

      class_type get(uint32_t targIndex) {

        //if (targIndex > (this->length - 1)) {
        //  throw;
        //}

        ArrayListNode<class_type>* node = this->getEntry(targIndex);

        if (node == NULL) {
          return (class_type)NULL;
        }

        return node->value;
      }

      void set(uint32_t targIndex, class_type value) {
        this->setEntry(targIndex, value);
      }

      void remove(uint32_t targIndex) {

        //if (targIndex > (this->length - 1)) {
        //  throw;
        //}

        this->deleteEntry(targIndex);
      }

      void push(class_type value) {
        uint32_t index = this->length;

        this->setEntry(index, value);
      }

      void unshift(class_type value) {
        uint32_t index = 0;

        this->insertEntry(index, value);
      }

      class_type pop() {
        uint32_t index = this->length - 1;

        ArrayListNode<class_type>* node = this->getEntry(index);

        if (node == NULL) {
          return NULL;
        }

        class_type outpValue = node->value;

        this->deleteEntry(index);

        return outpValue;
      }

      class_type shift() {
        uint32_t index = 0;

        ArrayListNode<class_type>* node = this->getEntry(index);

        if (node == NULL) {
          return NULL;
        }

        class_type outpValue = node->value;

        this->deleteEntry(index);

        return outpValue;
      }

//      ArrayList<class_type>* clone() {
//        ArrayList<class_type>* newList = new ArrayList<class_type>();
//
//        uint32_t listLen = this->getLength();
//
//        for (uint32_t idx = 0; idx < listLen; idx++) {
//          class_type entry = this->get(idx);
//
//          newList->push(entry);
//        }
//
//        return newList;
//      }

//      void concat(ArrayList<class_type> list) {
//        uint32_t listLen = list->getLength();
//
//        ArrayList<class_type>* newList = list->clone();
//
//        this->last->next = newList->root;
//        newList->root->prev = this->last;
//
//        //for (uint32_t idx = 0; idx < listLen; idx++) {
//        //  class_type entry = list->get(idx);
//
//        //  this->push(entry);
//        //}
//
//      }

  };

#endif
