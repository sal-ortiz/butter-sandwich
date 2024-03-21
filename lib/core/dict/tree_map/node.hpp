

#ifndef _TREE_MAP_NODE_HPP

  #define _TREE_MAP_NODE_HPP

  #include <stddef.h>


  template <typename data_type>
  struct TreeMapNode {
    TreeMapNode<data_type>* left;
    TreeMapNode<data_type>* right;

    const char* key;
    data_type value;
  };

#endif
