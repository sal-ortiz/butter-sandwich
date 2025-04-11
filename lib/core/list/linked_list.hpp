
#ifndef _LINKED_LIST_HPP

  #define _LINKED_LIST_HPP

  #include <stdint.h>
  #include <stdio.h>
  #include <math.h>

  #include <core/list/list.hpp>
  #include <core/list/node/linked_list_node.hpp>


  template <class class_type>
  class LinkedList: public List<class_type> {

    private:

      LinkedListNode<class_type>* root;
      LinkedListNode<class_type>* tail;
      LinkedListNode<class_type>* indexNode;

      uint32_t index;
      uint32_t length;

      LinkedListNode<class_type>* getEntry(uint32_t targIndex) override {
        LinkedListNode<class_type>* node;

        uint32_t curIndex;
        int8_t direction;

        uint32_t distFromRoot = targIndex;
        uint32_t distFromIndex = abs((int64_t)((uint32_t)targIndex - (uint32_t)this->index));
        uint32_t distFromTail = this->length - targIndex;

        bool canUpdateIndex = false;

        if (distFromRoot <= distFromIndex && distFromRoot <= distFromTail) {
          direction = 1;
          curIndex = 0;

          node = this->root->next;

        } else if (distFromIndex <= distFromRoot && distFromIndex <= distFromTail) {
          curIndex = this->index;
          node = this->indexNode;

          if (curIndex >= targIndex) {
            direction = -1;
          } else {
            direction = 1;
          }

          canUpdateIndex = true;

        } else {
          direction = -1;
          curIndex = this->length - 1;

          node = this->tail;
        }

        while (curIndex != targIndex) {

          if (node == NULL) {
            return NULL;
          }

          if (direction < 0) {
            node = node->prev;
          } else {
            node = node->next;
          }

          curIndex += direction;
        }

        if (canUpdateIndex == true) {
          this->indexNode = node;
          this->index = curIndex;
        }

        return node;
      }

      void setEntry(uint32_t targIndex, class_type value) override {
        LinkedListNode<class_type>* node;

        uint32_t curIndex;
        int8_t direction;

        uint32_t distFromRoot = targIndex;
        uint32_t distFromIndex = abs((int64_t)((uint32_t)targIndex - (uint32_t)this->index));
        uint32_t distFromTail = this->length - targIndex;

        bool canUpdateIndex = false;

        if (targIndex >= this->length) {
          direction = 1;
          curIndex = this->length - 1;

          node = this->tail;

        } else if (distFromRoot <= distFromIndex && distFromRoot <= distFromTail) {
          direction = 1;
          curIndex = 0;

          node = this->root;

        } else if (distFromIndex <= distFromRoot && distFromIndex <= distFromTail) {
          curIndex = this->index;
          node = this->indexNode;

          if (curIndex >= targIndex) {
            direction = -1;
          } else {
            direction = 1;
          }

          canUpdateIndex = true;

        } else {
          direction = -1;
          curIndex = this->length - 1;

          node = this->tail;
        }

        if (targIndex >= this->length) {
          this->length = targIndex + 1;
        }

        while (curIndex != targIndex) {

          if (direction > 0) {

            if (node->next == NULL) {
              node->next = new LinkedListNode<class_type>{};
              node->next->prev = node;

              node->next->value = (class_type)NULL;

              this->tail = node->next;
            }

            node = node->next;
          } else {

            node = node->prev;
          }
          curIndex += direction;
        }

        node->value = value;

        if (canUpdateIndex == true) {
          this->index = curIndex - 1;
          this->indexNode = node;
        }
      }

      void insertEntry(uint32_t targIndex, class_type value) override {

        if (targIndex >= this->length) {
          this->setEntry(targIndex, value);

          return;
        }

        LinkedListNode<class_type>* newNode = new LinkedListNode<class_type>{};
        LinkedListNode<class_type>* node = this->getEntry(targIndex);

        newNode->value = value;

        newNode->prev = node->prev;
        newNode->next = node;

        node->prev->next = newNode;

        if (node->next == NULL) {
          this->tail = node;
        }

        node->prev = newNode;

        this->indexNode = newNode;
        this->index = targIndex;

        this->length++;
      }

      void deleteEntry(uint32_t targIndex) override {
        LinkedListNode<class_type>* node = this->getEntry(targIndex);

        if (node == NULL) {
          return;
        }

        node->prev->next = node->next;

        if (node->next != NULL) {
          node->next->prev = node->prev;
        } else {
          this->tail = node->prev;
        }

        this->length--;

        //// TODO: make sure we're preserving our index node.
        //this->indexNode = node->prev;
        //this->index = targIndex/* - 1*/;

        delete node;
      }


    public:

      LinkedList() {
        this->length = 0;
        this->index = 0;

        this->root = new LinkedListNode<class_type>{};
        this->tail = this->root;
        this->indexNode = this->root;
      }

      ~LinkedList() {
        LinkedListNode<class_type>* node = this->root;

        while (node != NULL) {
          LinkedListNode<class_type>* next = node->next;

          delete node;

          node = next;
        }

      }

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

        LinkedList<class_type>* newList = list->clone();

        this->last->next = newList->root;
        newList->root->prev = this->last;

        //for (uint32_t idx = 0; idx < listLen; idx++) {
        //  class_type entry = list->get(idx);

        //  this->push(entry);
        //}

      }


  };

#endif
