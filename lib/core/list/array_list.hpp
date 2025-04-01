
#ifndef _ARRAY_LIST_HPP

  #define _ARRAY_LIST_HPP

  #include <stdint.h>
  #include <stdio.h>
  #include <math.h>

  #define _ARRAY_LIST_ALLOC_INCREMENT   64


  template <class class_type>
  class ArrayList {

    private:

      class_type* array;

      uint32_t arraySize;
      uint32_t length;

      void allocateArray(uint32_t newLen) {
        uint32_t arrayLen = this->arraySize / sizeof(class_type);
        uint32_t newSize = newLen * sizeof(class_type*);

        this->array = (class_type*)realloc(this->array, newSize);

        for (uint32_t idx = arrayLen; idx < newLen; idx++) {
          this->array[idx] = NULL;
        }

        this->arraySize = newSize;
      }

      class_type getEntry(uint32_t targIndex) {

        if (targIndex >= this->length) {
          return NULL;
        }

        return this->array[targIndex];
      }

      void setEntry(uint32_t targIndex, class_type value) {
        uint32_t arySize = this->arraySize;
        uint32_t targPtr = targIndex * sizeof(class_type);

        if (targPtr >= arySize) {
          this->allocateArray(targIndex + _ARRAY_LIST_ALLOC_INCREMENT);
        }

        this->array[targIndex] = value;

        if (targIndex >= this->length) {
          this->length = targIndex + 1;
        }

      }

      void insertEntry(uint32_t targIndex, class_type value) {

        for (uint32_t idx = this->length - 1; idx > targIndex; idx--) {
          class_type oldVal = this->getEntry(idx);

          this->setEntry(idx + 1, oldVal);
        }

        class_type lastEntry = this->getEntry(targIndex);

        this->setEntry(targIndex + 1, lastEntry);
        this->setEntry(targIndex, value);
      }

      void deleteEntry(uint32_t targIndex) {

        if (targIndex >= this->length) {
          return;
        }

        for (uint32_t idx = targIndex; idx < this->length; idx++) {
          class_type oldVal = this->getEntry(idx + 1);

          this->setEntry(idx, oldVal);
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
        class_type value = this->getEntry(targIndex);

        return value;
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

        class_type* value = this->getEntry(index);

        this->deleteEntry(index);

        return value;
      }

      class_type shift() {
        uint32_t index = 0;

        class_type value = this->getEntry(index);

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
