


#ifndef _LIST_HPP

  #define _LIST_HPP

  #include "./list/entry.hpp"
  #include <stdio.h>


  template <class class_type>
  class List {

    private:

      ListEntry<class_type>* root;

      unsigned long int length;

      ListEntry<class_type>* getEntry(unsigned long int targIndex) {
        ListEntry<class_type>* node = this->root;

        for (unsigned long int idx = 0; idx <= targIndex; idx++) {

          if (node->getNext() != (ListEntry<class_type>*)NULL) {
            node = node->getNext();
          } else {
            break;
          }

        }

        return node;
      }

      void setEntry(unsigned long int targIndex, class_type value) {
        ListEntry<class_type>* node = this->root;

        for (unsigned long int idx = 0; idx <= targIndex; idx++) {

          if (node->getNext() == (ListEntry<class_type>*)NULL) {
            ListEntry<class_type>* newEntry = new ListEntry<class_type>();

            newEntry->setValue((class_type)NULL);

            newEntry->setPrev(node);
            node->setNext(newEntry);
          }

          node = node->getNext();
        }

        if (targIndex >= this->length) {
          this->length = targIndex + 1;
        }

        node->setValue(value);
      }

      void insertEntry(unsigned long int targIndex, class_type value) {
        ListEntry<class_type>* newEntry = new ListEntry<class_type>();

        if (targIndex >= this->getLength()) {
          this->setEntry(targIndex, value);
        } else {

          ListEntry<class_type>* node = this->getEntry(targIndex);
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

        this->length = 0;
      }

      ListEntry<class_type>* getRoot() {
        return this->root;
      }

      unsigned long int getLength() {
        unsigned long int len = 0;

        ListEntry<class_type>* node = this->getRoot();

        while (node->getNext() != NULL) {
          len++;

          node = node->getNext();
        }

        return len;

        // TODO: returning this->length is much more efficient
        //       than traversing the list every time.
        //return this->length;
      }

      class_type get(unsigned long int targIndex) {

        //if (targIndex > (this->getLength() - 1)) {
        //  throw;
        //}

        ListEntry<class_type>* node = this->getEntry(targIndex);

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

        class_type outpValue = node->getValue();

        this->deleteEntry(index);

        return outpValue;
      }

      class_type shift() {
        unsigned long int index = 0;

        ListEntry<class_type>* node = this->getEntry(index);

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


