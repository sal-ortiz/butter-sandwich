
#ifndef _BINARY_TREE_LIST_NODE

  #define _BINARY_TREE_LIST_NODE

  #include <stdint.h>


  template <class class_type>
  class BinaryTreeListNode {

    private:

      class_type value;
      uint32_t index;

      BinaryTreeListNode<class_type>* left;
      BinaryTreeListNode<class_type>* right;


    public:

      BinaryTreeListNode() {
        this->left = NULL;
        this->right = NULL;

        //this->value = NULL;
      }

      uint32_t getIndex() {
        return this->index;
      }

      void setIndex(uint32_t idx) {
        this->index = idx;
      }

      class_type getValue() {
        return this->value;
      }

      void setValue(class_type value) {
        this->value = value;
      }

      BinaryTreeListNode<class_type>* getLeft() {
        return this->left;
      }

      void setLeft(BinaryTreeListNode<class_type>* node) {
        this->left = node;
      }

      BinaryTreeListNode<class_type>* getRight() {
        return this->right;
      }

      void setRight(BinaryTreeListNode<class_type>* node) {
        this->right = node;
      }

  };

#endif


