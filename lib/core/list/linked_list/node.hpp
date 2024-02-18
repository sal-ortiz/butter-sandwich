
#ifndef _LINKED_LIST_NODE_HPP

  #define _LINKED_LIST_NODE_HPP

  #include <stddef.h>


  template <class class_type>
  class LinkedListNode {

    private:

      class_type value;

      LinkedListNode<class_type>* next;
      LinkedListNode<class_type>* prev;


    public:

      LinkedListNode() {
        this->next = (LinkedListNode<class_type>*)NULL;
        this->prev = (LinkedListNode<class_type>*)NULL;

        //this->value = NULL;
      }

      class_type getValue() {
        return this->value;
      }

      void setValue(class_type value) {
        this->value = value;
      }

      LinkedListNode<class_type>* getNext() {
        return this->next;
      }

      void setNext(LinkedListNode<class_type>* node) {
        this->next = node;
      }

      LinkedListNode<class_type>* getPrev() {
        return this->prev;
      }

      void setPrev(LinkedListNode<class_type>* node) {
        this->prev = node;
      }

  };

#endif


