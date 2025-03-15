
#ifndef _BINARY_TREE_LIST_NODE

  #define _BINARY_TREE_LIST_NODE

  #include <stdint.h>


  template <class class_type>
  struct BinaryTreeListNode {

    BinaryTreeListNode<class_type>* left;
    BinaryTreeListNode<class_type>* right;

    class_type value;

    uint32_t index;
  };

#endif


