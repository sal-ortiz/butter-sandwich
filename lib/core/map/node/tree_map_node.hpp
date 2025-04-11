
#ifndef _TREE_MAP_NODE_HPP

  #define _TREE_MAP_NODE_HPP

  #include <stddef.h>
  #include <core/map/node/map_node.hpp>


  template <typename data_type>
  struct TreeMapNode: public MapNode<data_type> {

    TreeMapNode<data_type>* left;
    TreeMapNode<data_type>* right;
  };

#endif
