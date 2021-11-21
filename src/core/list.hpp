// Some Linked List action, for when we're ready to
// cash in seek efficiency in favor of epic write times.

#ifndef _LIST_HPP_
  #define _LIST_HPP_

//  #include "./base/tools.h"


  template <class class_type>
  class ListEntry {

    private:

      class_type val;

      ListEntry<class_type>* previous;
      ListEntry<class_type>* next;

    public:

      ListEntry() {
        previous = NULL;
        next = NULL;
        val = (class_type)NULL;
      }

      ListEntry(class_type initVal, ListEntry* prevEntry=NULL, ListEntry* nextEntry=NULL) {
        previous = prevEntry;
        next = nextEntry;
        val = initVal;
      }

      ListEntry(unsigned long int idVal, class_type initVal, ListEntry* prevEntry=NULL, ListEntry* nextEntry=NULL) {
        previous = prevEntry;
        next = nextEntry;
        val = initVal;
      }

      class_type getVal() {
        return val;
      }

      class_type set(class_type newVal) {
        return val = newVal;
      }

      bool hasNext() {
        return this->next != NULL;
      }

      bool hasPrevious() {
        return this->previous != NULL;
      }

      ListEntry* getNext() {
        return this->next;
      }

      ListEntry* getPrevious() {
        return this->previous;
      }

      class_type setNext(class_type newVal, unsigned long int idVal=NULL) {
        this->next = new ListEntry<class_type>(idVal, newVal, this);

        return (this->next)->getVal();
      }

      ListEntry<class_type>* setNext(ListEntry<class_type>* newVal) {
        return this->next = newVal;
      }

      class_type setPrevious(class_type newVal, unsigned long int idVal=NULL) {
        this->previous = new ListEntry<class_type>(newVal, idVal, NULL, this);

        return this->previous->getVal();
      }

      ListEntry<class_type>* setPrevious(ListEntry<class_type>* newVal) {
        return this->previous = newVal;
      }

      void clearNext() {
        delete [] this->next;
        this->next = NULL;
      }

      void clearPrevious() {
        delete [] this->previous;
        this->previous = NULL;
      }

      operator class_type () {
        return (class_type)this->getVal();
      }

  };  // class ListEntry













  template <class class_type>
  class List {

    private:

      ListEntry<class_type>* root;

    public:

      List(ListEntry<class_type>* newRoot=NULL) {
        this->setRoot(newRoot);
      }

      ListEntry<class_type>* getRoot() {
        return this->root;
      }

      ListEntry<class_type>* setRoot(ListEntry<class_type>* newRoot) {
        return this->root = newRoot;
      }

      class_type push(class_type newVal) {
        return this->push(NULL, newVal);
      }

      class_type push(unsigned long int idVal, class_type newVal) {
        ListEntry<class_type>* currentNode = getByIndex(length()-1);

        if (!currentNode) {
          ListEntry<class_type>* newRoot = new ListEntry<class_type>(idVal, newVal);

          setRoot(newRoot);

          return newRoot->getVal();
        } else {
          return currentNode->setNext(newVal, idVal);
        }

      }

      class_type pop() {
        ListEntry<class_type>* currentNode = getByIndex(length()-1);
        class_type retval;

        if (currentNode) {
          retval = currentNode->getVal();
        }

        if (currentNode && currentNode->hasPrevious()) {
          ListEntry<class_type>* prevNode = currentNode->getPrevious();

          prevNode->clearNext();

        } else if (currentNode) {
          //delete [] currentNode;
          currentNode = root = NULL;
        }

        return retval;
      };

      ListEntry<class_type>* getByIdentifier(unsigned long int idVal) {
        ListEntry<class_type>* currentNode = this->getRoot();

        while (currentNode && (currentNode->getIdentifier() != idVal)) {
          currentNode = currentNode->getNext();
        }

        return currentNode;
      }

      ListEntry<class_type>* getByIndex(signed long int index) {
        ListEntry<class_type>* currentNode = root;
        unsigned long int currentIndex = 0;

        while (currentNode && currentIndex < index) {
          currentIndex++;
          currentNode = currentNode->getNext();
        };

        if (currentIndex == index) {
          return currentNode;
        } else {
          return NULL;
        }

      }

      class_type operator[](const long int index) {
        ListEntry<class_type>* val = this->getByIndex(index);

        return val->getVal();
      }

      class_type get(const long int index) {
        ListEntry<class_type>* val = this->getByIndex(index);

        return val->getVal();
      }

      unsigned long int length() {
        ListEntry<class_type>* currentNode = root;
        unsigned long int numEntries = 0;

        while (currentNode) {
          numEntries++;

          currentNode = currentNode->getNext();
        }

        return numEntries;
      }

  };  // class List

#endif  // #ifndef _LIST_HPP_
