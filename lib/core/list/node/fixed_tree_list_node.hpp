
#ifndef _FIXED_TREE_LIST_NODE_HPP

  #define _FIXED_TREE_LIST_NODE_HPP

  #include <stddef.h>

  #include <core/list/node/list_node.hpp>


  template <typename data_type>
  struct FixedTreeListNode: public ListNode<data_type> {

    FixedTreeListNode<data_type>* left;
    FixedTreeListNode<data_type>* right;
  };

#endif
