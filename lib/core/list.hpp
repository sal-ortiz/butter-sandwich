
#ifndef _LIST_HPP

  #define _LIST_HPP

  #include "./list/entry.hpp"
  #include <stdio.h>


  template <class class_type>
  class List {

    private:

      ListEntry<class_type>* root;
      ListEntry<class_type>* indexEntry;

      unsigned long int index;
      unsigned long int length;

      ListEntry<class_type>* getEntry(unsigned long int targIndex) {

        if (targIndex < this->index) {
          this->indexEntry = this->root;
          this->index = 0;
        }

        ListEntry<class_type>* node = this->indexEntry;

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

      void setEntry(unsigned long int targIndex, class_type value) {

        if (targIndex < this->index) {
          this->indexEntry = this->root;
          this->index = 0;
        }

        ListEntry<class_type>* node = this->indexEntry;

        if (targIndex >= this->length) {
          this->length = targIndex + 1;
        }

        while ((this->index - 1) != targIndex) {

          if (node->getNext() == NULL) {
            ListEntry<class_type>* newEntry = new ListEntry<class_type>();

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

      void insertEntry(unsigned long int targIndex, class_type value) {

        if (targIndex >= this->getLength()) {
          this->setEntry(targIndex, value);
        } else {
          ListEntry<class_type>* newEntry = new ListEntry<class_type>();

          ListEntry<class_type>* node = this->getEntry(targIndex);

          if (node == NULL) {
            this->setEntry(targIndex, value);
          }

          ListEntry<class_type>* prev = node->getPrev();

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

      void deleteEntry(unsigned long int targIndex) {
        ListEntry<class_type>* node = this->getEntry(targIndex);

        if (node == NULL) {
          return;
        }

        ListEntry<class_type>* prev = node->getPrev();
        ListEntry<class_type>* next = node->getNext();

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

      List() {
        this->root = new ListEntry<class_type>();
        this->indexEntry = this->root;

        this->index = 0;
        this->length = 0;
      }

      ~List() {
        ListEntry<class_type>* node = this->root;

        while (node != NULL) {
          ListEntry<class_type>* next = node->getNext();

          delete node;

          node = next;
        }

      }

      ListEntry<class_type>* getRoot() {
        return this->root;
      }

      unsigned long int getLength() {
        return this->length;
      }

      class_type get(unsigned long int targIndex) {

        //if (targIndex > (this->getLength() - 1)) {
        //  throw;
        //}

        ListEntry<class_type>* node = this->getEntry(targIndex);

        if (node == NULL) {
          return (class_type)NULL;
        }

        return node->getValue();
      }

      void set(unsigned long int targIndex, class_type value) {
        this->setEntry(targIndex, value);
      }

      void remove(unsigned long int targIndex) {

        //if (targIndex > (this->getLength() - 1)) {
        //  throw;
        //}

        this->deleteEntry(targIndex);
      }

      void push(class_type value) {
        unsigned long int index = this->getLength();

        this->setEntry(index, value);
      }

      void unshift(class_type value) {
        unsigned long int index = 0;

        this->insertEntry(index, value);
      }

      class_type pop() {
        unsigned long int index = this->getLength() - 1;

        ListEntry<class_type>* node = this->getEntry(index);

        if (node == NULL) {
          return NULL;
        }

        class_type outpValue = node->getValue();

        this->deleteEntry(index);

        return outpValue;
      }

      class_type shift() {
        unsigned long int index = 0;

        ListEntry<class_type>* node = this->getEntry(index);

        if (node == NULL) {
          return NULL;
        }

        class_type outpValue = node->getValue();

        this->deleteEntry(index);

        return outpValue;
      }

      //void fill(class_type value, unsigned long int end=0, unsigned long int start=0) {
      //  unsigned long int endIdx;
      //
      //  if (end == 0) {
      //    endIdx = this->getLength() - 1;
      //  } else {
      //    endIdx = end;
      //  }
      //
      //  for (unsigned long int idx = start; idx <= endIdx; idx++) {
      //    this->setEntry(idx, value);
      //  }
      //
      //}

  };

#endif


