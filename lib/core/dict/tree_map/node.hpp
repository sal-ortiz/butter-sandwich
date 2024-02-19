

#ifndef _TREE_MAP_NODE_HPP

  #define _TREE_MAP_NODE_HPP

  #include <stddef.h>


  template <class class_type>
  class TreeMapNode {

    private:

      const char* key;
      class_type value;

      TreeMapNode<class_type>* left;
      TreeMapNode<class_type>* right;


    public:

      TreeMapNode() {
        this->left = (TreeMapNode<class_type>*)NULL;
        this->right = (TreeMapNode<class_type>*)NULL;

        //this->value == NULL;
      }

      const char* getKey() {
        return this->key;
      }

      void setKey(const char* key) {
        this->key = key;
      }

      class_type getValue() {
        return this->value;
      }

      void setValue(class_type value) {
        this->value = value;
      }

      TreeMapNode<class_type>* getLeft() {
        return this->left;
      }

      void setLeft(TreeMapNode<class_type>* node) {
        this->left = node;
      }

      TreeMapNode<class_type>* getRight() {
        return this->right;
      }

      void setRight(TreeMapNode<class_type>* node) {
        this->right = node;
      }

  };


#endif
