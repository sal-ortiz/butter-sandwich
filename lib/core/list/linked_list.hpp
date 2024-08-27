
#ifndef _LINKED_LIST_HPP

  #define _LINKED_LIST_HPP

  #include <stdint.h>
  #include <stdio.h>
  #include <math.h>

  #include "./linked_list/node.hpp"


  template <class class_type>
  class LinkedList {

    private:

      LinkedListNode<class_type>* root;
      LinkedListNode<class_type>* last;
      LinkedListNode<class_type>* indexNode;

      uint32_t index;
      uint32_t length;


      LinkedListNode<class_type>* getEntry(uint32_t targIndex) {
        if (targIndex >= this->length) {
          return NULL;
        }

        int index;
        LinkedListNode<class_type>* node;

        uint32_t distFromRoot = targIndex;
        uint32_t distFromIndex = abs((int)targIndex - (int)this->index);
        uint32_t distFromLast = this->length - (int)targIndex;
        int8_t direction = 1;

        if (distFromRoot <= distFromIndex && distFromRoot <= distFromLast) {
          node = this->root;
          index = 0;

          direction = 1;

        } else if (distFromIndex <= distFromRoot && distFromIndex <= distFromLast) {
          node = this->indexNode;
          index = this->index;

          if (targIndex < this->index) {
            direction = -1;
          } else {
            direction = 1;
          }

        } else if (distFromLast <= distFromRoot && distFromLast <= distFromIndex) {
          node = this->last->prev;
          index = this->length - 1;

          direction = -1;
        }

        while (index != targIndex) {
          LinkedListNode<class_type>* prev = node->prev;
          LinkedListNode<class_type>* next = node->next;

          index += direction;

          if (direction > 0 && next != NULL) {
            node = next;
          } else if (direction < 0 && prev != NULL) {
            node = prev;
          }

        }

        this->indexNode = node;
        this->index = index;

        return node->next;
      }

      void setEntry(uint32_t targIndex, class_type value) {
        uint32_t distFromRoot = targIndex;
        uint32_t distFromIndex = abs((int)targIndex - (int)this->index);
        uint32_t distFromLast = this->length - (int)targIndex;
        int8_t direction = 1;

        int index /*= this->index*/;
        LinkedListNode<class_type>* node /*= this->indexNode*/;

        if (distFromRoot <= distFromIndex && distFromRoot <= distFromLast) {
          node = this->root;
          index = 0;

          direction = 1;

        } else if (distFromIndex <= distFromRoot && distFromIndex <= distFromLast) {
          node = this->indexNode;
          index = this->index;

          if (targIndex < this->index) {
            direction = -1;
          } else {
            direction = 1;
          }

        } else if (distFromLast <= distFromRoot && distFromLast <= distFromIndex) {
          node = this->last->prev;
          index = this->length - 1;

          direction = -1;
        }

        if (targIndex >= this->length) {
          this->length = targIndex + 1;
        }

        while ((index - 1) != targIndex) {

          if (direction > 0 && node->next == NULL) {
            LinkedListNode<class_type>* newEntry = new LinkedListNode<class_type>{};

            newEntry->value = (class_type)NULL;

            newEntry->prev = node;
            node->next = newEntry;

            this->last = newEntry;
          }

          index += direction;

          if (direction > 0) {
            node = node->next;
          } else {
            node = node->prev;
          }

        }

        this->indexNode = node;
        this->index = index;

        node->value = value;
      }

      void insertEntry(uint32_t targIndex, class_type value) {

        if (targIndex >= this->length) {
          this->setEntry(targIndex, value);
        } else {
          LinkedListNode<class_type>* newEntry = new LinkedListNode<class_type>{};
          LinkedListNode<class_type>* node = this->getEntry(targIndex);

          LinkedListNode<class_type>* prev = node->prev;

          newEntry->value = value;

          newEntry->prev = prev;
          newEntry->next = node;

          node->prev = newEntry;

          if (prev) {
            prev->next = newEntry;
          }

          this->length++;
        }

      }

      void deleteEntry(uint32_t targIndex) {
        LinkedListNode<class_type>* node = this->getEntry(targIndex);

        if (node == NULL) {
          return;
        }

        LinkedListNode<class_type>* prev = node->prev;
        LinkedListNode<class_type>* next = node->next;

        if (prev) {
          prev->next = next;
        }

        if (next) {
          next->prev = prev;
        }

        this->length--;

        delete node;
      }


    public:

      LinkedList() {
        this->root = new LinkedListNode<class_type>{};
        this->indexNode = this->root;
        this->last = this->root;

        this->index = 0;
        this->length = 0;
      }

      ~LinkedList() {
        LinkedListNode<class_type>* node = this->root;

        while (node != NULL) {
          LinkedListNode<class_type>* next = node->next;

          delete node;

          node = next;
        }

      }

      //LinkedListNode<class_type>* getRoot() {
      //  return this->root;
      //}

      uint32_t getLength() {
        return this->length;
      }

      class_type get(uint32_t targIndex) {

        //if (targIndex > (this->length - 1)) {
        //  throw;
        //}

        LinkedListNode<class_type>* node = this->getEntry(targIndex);

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

        LinkedListNode<class_type>* node = this->getEntry(index);

        if (node == NULL) {
          return NULL;
        }

        class_type outpValue = node->value;

        this->deleteEntry(index);

        return outpValue;
      }

      class_type shift() {
        uint32_t index = 0;

        LinkedListNode<class_type>* node = this->getEntry(index);

        if (node == NULL) {
          return NULL;
        }

        class_type outpValue = node->value;

        this->deleteEntry(index);

        return outpValue;
      }

      //void fill(class_type value, uint32_t end=0, uint32_t start=0) {
      //  uint32_t endIdx;
      //
      //  if (end == 0) {
      //    endIdx = this->length - 1;
      //  } else {
      //    endIdx = end;
      //  }
      //
      //  for (uint32_t idx = start; idx <= endIdx; idx++) {
      //    this->setEntry(idx, value);
      //  }
      //
      //}

      LinkedList<class_type>* clone() {
        LinkedList<class_type>* newList = new LinkedList<class_type>();

        uint32_t listLen = this->getLength();

        for (uint32_t idx = 0; idx < listLen; idx++) {
          class_type entry = this->get(idx);

          newList->push(entry);
        }

        return newList;
      }

      void concat(LinkedList<class_type> list) {
        uint32_t listLen = list->getLength();

        for (uint32_t idx = 0; idx < listLen; idx++) {
          class_type entry = list->get(idx);

          this->push(entry);
        }

      }

  };

#endif
