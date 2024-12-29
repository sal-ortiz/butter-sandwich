

#ifndef _LIST_HPP

  #define _LIST_HPP

  #include "./list/linked_list.hpp"
  #include "./list/binary_tree_list.hpp"
  //#include "./list/static_tree_list.hpp"


  template <class class_type>
  //class List: public LinkedList<class_type> {
  //class List: public FixedBinaryTreeList<class_type> {
  class List: public BinaryTreeList<class_type> {
    // intentionally left blank.
  };


#endif
