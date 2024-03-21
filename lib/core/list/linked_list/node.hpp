
#ifndef _LINKED_LIST_NODE_HPP

  #define _LINKED_LIST_NODE_HPP

  #include <stddef.h>


  template <typename data_type>
  struct LinkedListNode {

    LinkedListNode<data_type>* next;
    LinkedListNode<data_type>* prev;

    data_type value;
  };

#endif


