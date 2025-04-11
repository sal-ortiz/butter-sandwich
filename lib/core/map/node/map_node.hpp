
#ifndef _MAP_NODE_HPP

  #define _MAP_NODE_HPP

  #include <stddef.h>
  #include <core/map/node/map_node.hpp>


  template <typename data_type>
  struct MapNode {

    const char* key;
    data_type value;
  };

#endif
