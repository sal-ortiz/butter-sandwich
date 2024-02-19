
#ifndef _DICT_HPP

  #define _DICT_HPP

  #include "./dict/hash_map.hpp"
  #include "./dict/tree_map.hpp"


  template <class class_type>
  //class Dict: public HashMap<class_type> {
  class Dict: public TreeMap<class_type> {
    // intentionally left blank.
  };


#endif
