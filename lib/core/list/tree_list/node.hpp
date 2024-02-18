

#ifndef _TREE_LIST_NODE_HPP

  #define _TREE_LIST_NODE_HPP

  #include <stddef.h>


  template <class class_type>
  class TreeListNode {

    private:

      uint32_t index;
      class_type value;

      TreeListNode<class_type>* left;
      TreeListNode<class_type>* right;


    public:

      TreeListNode() {
        this->left = (TreeListNode<class_type>*)NULL;
        this->right = (TreeListNode<class_type>*)NULL;

        //this->value == NULL;
      }

      uint32_t getIndex() {
        return this->index;
      }

      void setIndex(uint32_t newIndex) {
        this->index = newIndex;
      }

      class_type getValue() {
        return this->value;
      }

      void setValue(class_type value) {
        this->value = value;
      }

      TreeListNode<class_type>* getLeft() {
        return this->left;
      }

      void setLeft(TreeListNode<class_type>* node) {
        //node->setPrev(this);

        this->left = node;
      }

      TreeListNode<class_type>* getRight() {
        return this->right;
      }

      void setRight(TreeListNode<class_type>* node) {
        //node->setPrev(this);

        this->right = node;
      }

  };


#endif
