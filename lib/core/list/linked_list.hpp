
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

      LinkedListNode<class_type>* head;
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

        if (distFromTail <= distFromIndex && distFromTail <= distFromRoot) {
          curIndex = this->length - 1;

          node = this->tail;

          if (targIndex <= curIndex) {
            direction = -1;
          } else {
            direction = 1;
          }

        } else if (distFromRoot <= distFromIndex && distFromRoot <= distFromTail) {
          direction = 1;
          curIndex = 0;

          node = this->head;

        } else if (distFromIndex <= distFromRoot && distFromIndex <= distFromTail) {
          curIndex = this->index;
          node = this->indexNode;

          if (curIndex > targIndex) {
            direction = -1;
          } else {
            direction = 1;
          }

        }

        while (curIndex != targIndex) {

          if (direction >= 0) {
            node = node->next;
          } else {
            node = node->prev;
          }

          curIndex += direction;
        }

        if (curIndex > 0 && curIndex < this->length - 1) {
          this->index = curIndex;
          this->indexNode = node;
        }

        return node;
      }

      void setEntry(uint32_t targIndex, class_type value) override {
        LinkedListNode<class_type>* node;

        if (targIndex == 0) {
          this->head->value = value;

          if (this->length == 0) {
            this->length++;
          }

          return;
        }

        if (targIndex == this->length - 1) {
          this->tail->value = value;
        }

        uint32_t curIndex;
        int8_t direction;

        uint32_t distFromRoot = targIndex;
        uint32_t distFromIndex = abs((int64_t)((uint32_t)targIndex - (uint32_t)this->index));
        uint32_t distFromTail = this->length - targIndex;

        if (distFromTail <= distFromIndex && distFromTail <= distFromRoot) {
          curIndex = this->length - 1;

          node = this->tail;

          if (curIndex > targIndex) {
            direction = -1;
          } else {
            direction = 1;
          }

        } else if (distFromRoot <= distFromIndex && distFromRoot <= distFromTail) {
          direction = 1;
          curIndex = 0;

          node = this->head;

        } else if (distFromIndex <= distFromRoot && distFromIndex <= distFromTail) {
          curIndex = this->index;
          node = this->indexNode;

          if (curIndex > targIndex) {
            direction = -1;
          } else {
            direction = 1;
          }

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

        if (targIndex >= this->length) {
          this->length = targIndex + 1;
        }

        if (curIndex > 0 && curIndex < this->length - 1) {
          this->index = curIndex;
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

        node->prev = newNode;
        newNode->next = node;

        if (targIndex == 0) {
          this->head = newNode;
        }

        newNode->value = value;

        if (targIndex > 0 && targIndex < this->length - 1) {
          this->indexNode = newNode;
          this->index = targIndex;
        }

        this->length++;
      }

      void deleteEntry(uint32_t targIndex) override {

        if (targIndex >= this->length) {
          return;
        }

        if (this->length < 2) {
          this->head->value = NULL;
          this->length = 0;

          return;
        }


        LinkedListNode<class_type>* node = this->getEntry(targIndex);

        //if (node == NULL) {
        //  return;
        //}

        if (node->prev != NULL) {
          node->prev->next = node->next;
        }

        if (node->next != NULL) {
          node->next->prev = node->prev;
        }

        if (targIndex == 0) {
          this->head = node->next;
        }

        if (targIndex == this->length - 1) {
          this->indexNode = node->prev;

          this->index = targIndex - 1;
        } else {
          this->indexNode = node->next;

          this->index = targIndex;
        }

        delete node;

        this->length--;
      }

      void sortList(int8_t(*func)(class_type, class_type), uint32_t startIdx, uint32_t endIdx, uint32_t depth=0) {
        // merge sort
        uint32_t leftStartIdx = startIdx;
        //uint32_t leftEndIdx = startIdx + floor(endIdx / 2);
        uint32_t leftEndIdx = startIdx + floor((endIdx - startIdx) / 2);

        uint32_t rightStartIdx = leftEndIdx + 1;
        uint32_t rightEndIdx = endIdx;

        if ((leftEndIdx - leftStartIdx) >= 1) {
          this->sortList(func, leftStartIdx, leftEndIdx, depth+1);
        }

        if ((rightEndIdx - rightStartIdx) >= 1) {
          this->sortList(func, rightStartIdx, rightEndIdx, depth+1);
        }

        LinkedListNode<class_type>* leftStart = this->getEntry(leftStartIdx);
        LinkedListNode<class_type>* rightStart = this->getEntry(rightStartIdx);

        int8_t cmp = func(leftStart->value, rightStart->value);

        if (cmp > 0) {

          LinkedListNode<class_type>* leftEnd = this->getEntry(leftEndIdx);
          LinkedListNode<class_type>* rightEnd = this->getEntry(rightEndIdx);

          rightStart->prev = leftStart->prev;
          leftStart->prev = rightEnd;

          leftEnd->next = rightEnd->next;
          rightEnd->next = leftStart;


          if (rightStart->prev) {
            rightStart->prev->next = rightStart;
          }

          if (leftEnd->next) {
            leftEnd->next->prev = leftEnd;
          }


          if (rightEnd->next) {
            rightEnd->next->prev = rightEnd;
          }

          if (leftStart->prev) {
            leftStart->prev->next = leftStart;
          }



          if (startIdx == 0) {
            this->head = rightStart;
          }

          if (endIdx == (this->length - 1)) {
            this->tail = leftEnd;
          }

          this->indexNode = this->head;
          this->index = 0;
        }

      }


    public:

      LinkedList() {
        this->length = 0;
        this->index = 0;

        this->head = new LinkedListNode<class_type>();
        this->tail = this->head;
        this->indexNode = this->head;
      }

      ~LinkedList() {
        LinkedListNode<class_type>* node = this->head;

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

        //if (node == NULL) {
        //  return NULL;
        //}

        class_type outpValue = node->value;

        this->deleteEntry(index);

        return outpValue;
      }

      class_type shift() {
        uint32_t index = 0;

        LinkedListNode<class_type>* node = this->getEntry(index);

        //if (node == NULL) {
        //  return NULL;
        //}

        class_type outpValue = node->value;

        this->deleteEntry(index);

        return outpValue;
      }

      LinkedList<class_type>* clone(uint32_t startIdx=0, uint32_t len=0) {
        LinkedList<class_type>* newList = new LinkedList<class_type>();

        uint32_t listLen = len || this->getLength();

        for (uint32_t idx = startIdx; idx < listLen; idx++) {
          class_type val = this->get(idx);

          newList->push(val);
        }

        return newList;
      }

      void concat(LinkedList<class_type>* list) {
        this->tail->next = list->head;
        list->head->prev = this->tail;

        this->tail = list->tail;

        this->length += list->getLength();
      }

      void sort(int8_t(*func)(class_type, class_type)) {
        uint32_t start = 0;
        uint32_t end = this->length - 1;

        this->sortList(func, start, end);
      }

  };

#endif
