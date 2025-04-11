
#ifndef _BINARY_TREE_LIST_NODE

  #define _BINARY_TREE_LIST_NODE

  #include <stdint.h>

  #include "./list_node.hpp"


  template <typename data_type>
  struct BinaryTreeListNode: public ListNode<data_type> {

    BinaryTreeListNode<data_type>* left;
    BinaryTreeListNode<data_type>* right;

    uint32_t index;
  };

#endif
