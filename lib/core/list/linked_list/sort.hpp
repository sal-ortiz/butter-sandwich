// C++ program for merge sort on doubly linked list


#ifndef _LINKED_LIST_SORT_HPP

  #define _LINKED_LIST_SORT_HPP

  #include <stdint.h>
  #include <core/list/node/linked_list_node.hpp>


  template <class class_type>
  class LinkedListSort {

    private:

      static LinkedListNode<class_type>* split(LinkedListNode<class_type>* head) {
        LinkedListNode<class_type>* hare = head;
        LinkedListNode<class_type>* tort = head;

          while (hare != NULL && hare->next != NULL && hare->next->next != NULL) {
            hare = hare->next->next;
            tort = tort->next;
          }

          LinkedListNode<class_type>* tmp = tort->next;

          tort->next = NULL;

          if (tmp != NULL) {
            tmp->prev = NULL;
          }

          return tmp;
      }

      static LinkedListNode<class_type>* merge(LinkedListNode<class_type>* left, LinkedListNode<class_type>* right, int32_t(*func)(class_type, class_type)) {

          if (left == NULL) {
            return right;
          }

          if (right == NULL) {
            return left;
          }

          int32_t cmp = func(left->value, right->value);

          if (cmp < 0) {
            left->next = LinkedListSort::merge(left->next, right, func);

            if (left->next != NULL) {
              left->next->prev = left;
            }

            left->prev = NULL;

            return left;

          } else {
            right->next = LinkedListSort::merge(left, right->next, func);

            if (right->next != NULL) {
              right->next->prev = right;
            }

            right->prev = NULL;

            return right;
          }

      }


    public:

      static LinkedListNode<class_type>* mergeSort(LinkedListNode<class_type>* head, int32_t(*func)(class_type, class_type)) {

        if (head == NULL || head->next == NULL) {
          return head;
        }

        LinkedListNode<class_type>* right = LinkedListSort<class_type>::split(head);

        head = LinkedListSort<class_type>::mergeSort(head, func);
        right = LinkedListSort<class_type>::mergeSort(right, func);

        return LinkedListSort::merge(head, right, func);
      }

  };

#endif
