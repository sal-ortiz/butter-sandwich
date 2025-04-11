
#ifndef _LINKED_LIST_NODE_HPP

  #define _LINKED_LIST_NODE_HPP

  #include <stddef.h>

  #include <core/list/node/list_node.hpp>


  template <typename data_type>
  struct LinkedListNode: public ListNode<data_type> {

    LinkedListNode<data_type>* next;
    LinkedListNode<data_type>* prev;
  };

#endif
