

#ifndef _LIST_HPP

  #define _LIST_HPP

  #include "./list/linked_list.hpp"
  #include "./list/binary_tree_list.hpp"
  #include "./list/fixed_tree_list.hpp"
  #include "./list/array_list.hpp"


  template <class class_type>
  //class List: public LinkedList<class_type> {
  //class List: public ArrayList<class_type> {
  class List: public FixedTreeList<class_type> {
  //class List: public BinaryTreeList<class_type> {
    // intentionally left blank.
  };


#endif
