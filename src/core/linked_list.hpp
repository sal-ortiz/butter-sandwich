// Some Linked List action, for when we're ready to
// cash in seek efficiency in favor of epic write times.

#ifndef _LINKED_LIST_HPP_
  #define _LINKED_LIST_HPP_

  #include "./tools.h"
  #include "./container_base.hpp"


  template <class class_type>
  class LinkedListEntry: public ContainerBase {

    private:

      class_type val;

      LinkedListEntry<class_type>* previous;
      LinkedListEntry<class_type>* next;

    public:

      LinkedListEntry() {
        this->setIdentifier(NULL);

        previous = NULL;
        next = NULL;
        val = (class_type)NULL;
      }

      LinkedListEntry(class_type initVal, LinkedListEntry* prevEntry=NULL, LinkedListEntry* nextEntry=NULL) {
        this->setIdentifier(NULL);

        previous = prevEntry;
        next = nextEntry;
        val = initVal;
      }

      LinkedListEntry(unsigned long int idVal, class_type initVal, LinkedListEntry* prevEntry=NULL, LinkedListEntry* nextEntry=NULL) {
        this->setIdentifier(idVal);

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

      LinkedListEntry* getNext() {
        return this->next;
      }

      LinkedListEntry* getPrevious() {
        return this->previous;
      }

      class_type setNext(class_type newVal, unsigned long int idVal=NULL) {
        this->next = new LinkedListEntry<class_type>(idVal, newVal, this);

        return (this->next)->getVal();
      }

      LinkedListEntry<class_type>* setNext(LinkedListEntry<class_type>* newVal) {
        return this->next = newVal;
      }

      class_type setPrevious(class_type newVal, unsigned long int idVal=NULL) {
        this->previous = new LinkedListEntry<class_type>(newVal, idVal, NULL, this);

        return this->previous->getVal();
      }

      LinkedListEntry<class_type>* setPrevious(LinkedListEntry<class_type>* newVal) {
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
        return this->getVal();
      }

  };  // class LinkedListEntry


  template <class class_type>
  class LinkedList {

    private:

      LinkedListEntry<class_type>* root;

    public:

      LinkedList(LinkedListEntry<class_type>* newRoot=NULL) {
        this->setRoot(newRoot);
      }

      LinkedListEntry<class_type>* getRoot() {
        return this->root;
      }

      LinkedListEntry<class_type>* setRoot(LinkedListEntry<class_type>* newRoot) {
        return this->root = newRoot;
      }

      class_type push(class_type newVal) {
        return this->push(NULL, newVal);
      }

      class_type push(unsigned long int idVal, class_type newVal) {
        LinkedListEntry<class_type>* currentNode = getByIndex(length()-1);

        if (!currentNode) {
          LinkedListEntry<class_type>* newRoot = new LinkedListEntry<class_type>(idVal, newVal);

          setRoot(newRoot);

          return newRoot->getVal();
        } else {
          return currentNode->setNext(newVal, idVal);
        }

      }

      class_type pop() {
        LinkedListEntry<class_type>* currentNode = getByIndex(length()-1);
        class_type retval;

        if (currentNode) {
          retval = currentNode->getVal();
        }

        if (currentNode && currentNode->hasPrevious()) {
          LinkedListEntry<class_type>* prevNode = currentNode->getPrevious();

          prevNode->clearNext();

        } else if (currentNode) {
          //delete [] currentNode;
          currentNode = root = NULL;
        }

        return retval;
      };

      LinkedListEntry<class_type>* getByIdentifier(unsigned long int idVal) {
        LinkedListEntry<class_type>* currentNode = this->getRoot();

        while (currentNode && (currentNode->getIdentifier() != idVal)) {
          currentNode = currentNode->getNext();
        }

        return currentNode;
      }

      LinkedListEntry<class_type>* getByIndex(signed long int index) {
        LinkedListEntry<class_type>* currentNode = root;
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

      unsigned long int length() {
        LinkedListEntry<class_type>* currentNode = root;
        unsigned long int numEntries = 0;

        while (currentNode) {
          numEntries++;

          currentNode = currentNode->getNext();
        }

        return numEntries;
      }

  };  // class LinkedList

#endif  // #ifndef _LINKED_LIST_HPP_
