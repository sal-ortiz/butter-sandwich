
#ifndef _FIXED_TREE_LIST_NODE_HPP

  #define _FIXED_TREE_LIST_NODE_HPP

  #include <stddef.h>


  template <class class_type>
  struct FixedTreeListNode {

      FixedTreeListNode<class_type>* left;
      FixedTreeListNode<class_type>* right;

      class_type value;
  };

#endif


