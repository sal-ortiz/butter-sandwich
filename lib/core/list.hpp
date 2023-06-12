


#ifndef _LIST_HPP

  #define _LIST_HPP

  #include "./list/entry.hpp"


  template <class class_type>
  class List {

    private:

      ListEntry<class_type>* root;

      ListEntry<class_type>* getEntry(unsigned long int targIndex) {
        ListEntry<class_type>* node = this->root;

        for (unsigned long int idx = 0; idx < targIndex + 1; idx++) {

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

        node->setValue(value);
      }

      void deleteEntry(unsigned long int targIndex) {
        unsigned long int length = this->getLength();

        ListEntry<class_type>* node = this->getEntry(targIndex);

        ListEntry<class_type>* prev = node->getPrev();
        ListEntry<class_type>* next = node->getNext();

        if (prev) {
          prev->setNext(next);
        }

        if (next) {
          next->setPrev(prev);
        }

        delete node;
      }


    public:

      List() {
        this->root = new ListEntry<class_type>();
      }

      ListEntry<class_type>* getRoot() {
        return this->root;
      }

      unsigned long int getLength() {
        unsigned long int length = 0;

        ListEntry<class_type>* node = this->root;

        while (node->getNext() != (ListEntry<class_type>*)NULL) {
          length++;

          node = node->getNext();
        }

        return length;
      }

      class_type get(unsigned long int targIndex) {

        if (targIndex > (this->getLength() - 1)) {
          throw;
        }

        ListEntry<class_type>* node = this->getEntry(targIndex);

        return node->getValue();
      }

      void set(unsigned long int targIndex, class_type value) {
        this->setEntry(targIndex, value);
      }

      void remove(unsigned long int targIndex) {

        if (targIndex > (this->getLength() - 1)) {
          throw;
        }

        this->deleteEntry(targIndex);
      }

      void push(class_type value) {
        unsigned long int length = this->getLength();

        ListEntry<class_type>* newEntry = new ListEntry<class_type>();
        ListEntry<class_type>* node = this->getEntry(length - 1);

        newEntry->setValue(value);

        newEntry->setPrev(node);
        node->setNext(newEntry);
      }

      void unshift(class_type value) {
        ListEntry<class_type>* newEntry = new ListEntry<class_type>();
        ListEntry<class_type>* root = this->getRoot();
        ListEntry<class_type>* next = root->getNext();

        newEntry->setValue(value);

        root->setNext(newEntry);

        newEntry->setPrev(root);

        if (next != (ListEntry<class_type>*)NULL) {
          newEntry->setNext(next);

          next->setPrev(newEntry);
        }

      }

      class_type pop() {
        unsigned long int length = this->getLength();

        ListEntry<class_type>* node = this->getEntry(length - 1);
        ListEntry<class_type>* prev = this->getEntry(length - 2);

        prev->setNext((ListEntry<class_type>*)NULL);

        node->setNext((ListEntry<class_type>*)NULL);
        node->setPrev((ListEntry<class_type>*)NULL);

        class_type outpValue = node->getValue();

        delete node;

        return outpValue;
      }

      class_type shift() {
        ListEntry<class_type>* root = this->getRoot();
        ListEntry<class_type>* next = root->getNext();

        if (next != (ListEntry<class_type>*)NULL) {
          ListEntry<class_type>* further = next->getNext();


          if (further) {
            root->setNext(further);
            further->setPrev(root);
          }

          next->setPrev((ListEntry<class_type>*)NULL);
          next->setNext((ListEntry<class_type>*)NULL);
        }

        class_type outpValue = next->getValue();

        delete next;

        return outpValue;
      }

      void fill(class_type value, unsigned long int end=0, unsigned long int start=0) {
        unsigned long int endIdx;

        if (end == 0) {
          endIdx = this->getLength() - 1;
        } else {
          endIdx = end;
        }

        for (unsigned long int idx = start; idx <= endIdx; idx++) {
          this->setEntry(idx, value);
        }

      }

  };

#endif


