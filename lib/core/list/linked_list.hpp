
#ifndef _LINKED_LIST_HPP

  #define _LINKED_LIST_HPP

  #include <stdint.h>
  #include <stdio.h>

  #include "./linked_list/node.hpp"


  template <class class_type>
  class LinkedList {

    private:

      LinkedListNode<class_type>* root;
      LinkedListNode<class_type>* indexEntry;

      uint32_t index;
      uint32_t length;

      LinkedListNode<class_type>* getEntry(uint32_t targIndex) {

        if (targIndex < this->index) {
          this->indexEntry = this->root;
          this->index = 0;
        }

        LinkedListNode<class_type>* node = this->indexEntry;

        if (targIndex >= this->length) {
          return NULL;
        }

        while (this->index != targIndex) {

          if (node->getNext() != NULL) {
            node = node->getNext();

            this->index++;
          }

        }

        this->indexEntry = node;

        return node->getNext();
      }

      void setEntry(uint32_t targIndex, class_type value) {

        if (targIndex < this->index) {
          this->indexEntry = this->root;
          this->index = 0;
        }

        LinkedListNode<class_type>* node = this->indexEntry;

        if (targIndex >= this->length) {
          this->length = targIndex + 1;
        }

        while ((this->index - 1) != targIndex) {

          if (node->getNext() == NULL) {
            LinkedListNode<class_type>* newEntry = new LinkedListNode<class_type>();

            newEntry->setValue((class_type)NULL);

            newEntry->setPrev(node);
            node->setNext(newEntry);
          }

          this->index++;

          node = node->getNext();
        }

        this->indexEntry = node;

        node->setValue(value);
      }

      void insertEntry(uint32_t targIndex, class_type value) {

        if (targIndex >= this->getLength()) {
          this->setEntry(targIndex, value);
        } else {
          LinkedListNode<class_type>* newEntry = new LinkedListNode<class_type>();

          LinkedListNode<class_type>* node = this->getEntry(targIndex);

          if (node == NULL) {
            this->setEntry(targIndex, value);
          }

          LinkedListNode<class_type>* prev = node->getPrev();

          newEntry->setValue(value);

          newEntry->setPrev(prev);
          newEntry->setNext(node);

          node->setPrev(newEntry);

          if (prev) {
            prev->setNext(newEntry);
          }

          this->length++;
        }

      }

      void deleteEntry(uint32_t targIndex) {
        LinkedListNode<class_type>* node = this->getEntry(targIndex);

        if (node == NULL) {
          return;
        }

        LinkedListNode<class_type>* prev = node->getPrev();
        LinkedListNode<class_type>* next = node->getNext();

        if (prev) {
          prev->setNext(next);
        }

        if (next) {
          next->setPrev(prev);
        }

        this->length--;

        delete node;
      }


    public:

      LinkedList() {
        this->root = new LinkedListNode<class_type>();
        this->indexEntry = this->root;

        this->index = 0;
        this->length = 0;
      }

      ~LinkedList() {
        LinkedListNode<class_type>* node = this->root;

        while (node != NULL) {
          LinkedListNode<class_type>* next = node->getNext();

          delete node;

          node = next;
        }

      }

      LinkedListNode<class_type>* getRoot() {
        return this->root;
      }

      uint32_t getLength() {
        return this->length;
      }

      class_type get(uint32_t targIndex) {

        //if (targIndex > (this->getLength() - 1)) {
        //  throw;
        //}

        LinkedListNode<class_type>* node = this->getEntry(targIndex);

        if (node == NULL) {
          return (class_type)NULL;
        }

        return node->getValue();
      }

      void set(uint32_t targIndex, class_type value) {
        this->setEntry(targIndex, value);
      }

      void remove(uint32_t targIndex) {

        //if (targIndex > (this->getLength() - 1)) {
        //  throw;
        //}

        this->deleteEntry(targIndex);
      }

      void push(class_type value) {
        uint32_t index = this->getLength();

        this->setEntry(index, value);
      }

      void unshift(class_type value) {
        uint32_t index = 0;

        this->insertEntry(index, value);
      }

      class_type pop() {
        uint32_t index = this->getLength() - 1;

        LinkedListNode<class_type>* node = this->getEntry(index);

        if (node == NULL) {
          return NULL;
        }

        class_type outpValue = node->getValue();

        this->deleteEntry(index);

        return outpValue;
      }

      class_type shift() {
        uint32_t index = 0;

        LinkedListNode<class_type>* node = this->getEntry(index);

        if (node == NULL) {
          return NULL;
        }

        class_type outpValue = node->getValue();

        this->deleteEntry(index);

        return outpValue;
      }

      //void fill(class_type value, uint32_t end=0, uint32_t start=0) {
      //  uint32_t endIdx;
      //
      //  if (end == 0) {
      //    endIdx = this->getLength() - 1;
      //  } else {
      //    endIdx = end;
      //  }
      //
      //  for (uint32_t idx = start; idx <= endIdx; idx++) {
      //    this->setEntry(idx, value);
      //  }
      //
      //}

  };

#endif


