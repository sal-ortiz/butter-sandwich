
#ifndef _ARRAY_LIST_HPP

  #define _ARRAY_LIST_HPP

  #include <stdint.h>
  #include <stdio.h>
  #include <math.h>

  #include <core/list/list.hpp>
  #include <core/list/node/array_list_node.hpp>

  #define _ARRAY_LIST_ALLOC_INCREMENT   64


  template <class class_type>
  class ArrayList: List<class_type> {

    private:

      ArrayListNode<class_type>** array;

      uint32_t arraySize;
      uint32_t length;

      void allocateArray(uint32_t newLen) {
        uint32_t arrayLen = this->arraySize / sizeof(ArrayListNode<class_type>*);
        uint32_t newSize = newLen * sizeof(ArrayListNode<class_type>*);

        this->array = (ArrayListNode<class_type>**)realloc(this->array, newSize);

        for (uint32_t idx = arrayLen; idx < newLen; idx++) {
          this->array[idx] = NULL;
        }

        this->arraySize = newSize;
      }

      ArrayListNode<class_type>* getEntry(uint32_t targIndex) override {

        if (targIndex >= this->length) {
          return NULL;
        }

        return this->array[targIndex];
      }

      void setEntry(uint32_t targIndex, class_type value) override {

        if (targIndex >= this->length) {
          uint32_t arySize = this->arraySize;
          uint32_t targPtr = targIndex * sizeof(ArrayListNode<class_type>*);

          if (targPtr >= arySize) {
            this->allocateArray(targIndex + _ARRAY_LIST_ALLOC_INCREMENT);
          }

          ArrayListNode<class_type>* newNode = new ArrayListNode<class_type>();

          newNode->value = value;

          this->array[targIndex] = newNode;
          this->length = targIndex + 1;

        } else {
          this->array[targIndex]->value = value;
        }

      }

      void insertEntry(uint32_t targIndex, class_type value) override {

        if (targIndex >= this->length) {
          this->setEntry(targIndex, value);

          return;
        }

        uint32_t listLen = this->length;
        uint32_t newSize = (listLen + 1) * sizeof(ArrayListNode<class_type>*);

        if (newSize >= this->arraySize) {
          this->allocateArray(this->length + _ARRAY_LIST_ALLOC_INCREMENT);
        }

        for (uint32_t idx = listLen; idx > targIndex; idx--) {
          ArrayListNode<class_type>* node = this->array[idx - 1];

          this->array[idx] = node;
        }

        ArrayListNode<class_type>* newNode = new ArrayListNode<class_type>();

        newNode->value = value;

        this->array[targIndex] = newNode;
        this->length++;
      }

      void deleteEntry(uint32_t targIndex) override {

        if (targIndex >= this->length) {
          return;
        }

        ArrayListNode<class_type>* targNode = this->array[targIndex];

        delete targNode;

        for (uint32_t idx = targIndex; idx < this->length; idx++) {
          ArrayListNode<class_type>*  oldEntry = this->array[idx + 1];

          this->array[idx] = oldEntry;
        }

        this->array[this->length - 1] = NULL;

        this->length--;
      }


    public:

      ArrayList() {
        this->length = 0;

        //this->array = NULL;
        this->allocateArray(_ARRAY_LIST_ALLOC_INCREMENT);
      }

      ~ArrayList() {

        for (uint32_t idx = 0; idx < this->length; idx++) {
          ArrayListNode<class_type>* node = this->array[idx];

          delete node;
        }

        free(this->array);
      }

      uint32_t getLength() {
        return this->length;
      }

      class_type get(uint32_t targIndex) {
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

        class_type value = this->get(index);

        this->deleteEntry(index);

        return value;
      }

      class_type shift() {
        uint32_t index = 0;

        class_type value = this->get(index);

        this->deleteEntry(index);

        return value;
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
