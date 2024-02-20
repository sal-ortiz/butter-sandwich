

#ifndef _TREE_MAP_HPP

  #define _TREE_MAP_HPP

  #include <stdio.h>
  #include <stdint.h>
  #include <string.h>
  #include "./tree_map/node.hpp"


  template <class class_type>
  class TreeMap {

    private:

      TreeMapNode<class_type>* root;

      class_type getEntry(const char* key) {
        TreeMapNode<class_type>* node = getEntry(this->root, key);

        if (node != NULL) {
          return node->getValue();
        }

        return (class_type)NULL;
      }

      TreeMapNode<class_type>* getEntry(TreeMapNode<class_type>* node, const char* key) {

        if (node == NULL) {
          return NULL;
        }

        const char* nodeKey = node->getKey();
        uint8_t keyCmp = strcmp(key, nodeKey);

        TreeMapNode<class_type>* left = NULL;
        TreeMapNode<class_type>* right = NULL;

        if (keyCmp == 0) {
          return node;
        } else if (keyCmp < 0) {
          left = getEntry(node->getLeft(), key);
        } else if (keyCmp > 0) {
          right = getEntry(node->getRight(), key);
        }

        if (left) {
          return left;
        } else {
          return right;
        }

      }

      void setEntry(const char* key, class_type value) {
        this->root = this->setEntry(this->root, key, value);
      }

      TreeMapNode<class_type>* setEntry(TreeMapNode<class_type>* node, const char* key, class_type value) {

        if (node == NULL) {
          TreeMapNode<class_type>* newNode = new TreeMapNode<class_type>();

          newNode->setKey(key);
          newNode->setValue(value);

          return newNode;
        }

        const char* nodeKey = node->getKey();
        uint8_t keyCmp = strcmp(key, nodeKey);

        if (keyCmp < 0) {
          TreeMapNode<class_type>* leftNode = node->getLeft();
          TreeMapNode<class_type>* tmpLeft = this->setEntry(leftNode, key, value);

          node->setLeft(tmpLeft);

        } else if (keyCmp > 0) {
          TreeMapNode<class_type>* rightNode = node->getRight();
          TreeMapNode<class_type>* tmpRight = this->setEntry(rightNode, key, value);

          node->setRight(tmpRight);

        } else {
          node->setValue(value);
        }

        return node;
      }


      List<const char*>* getKeys(TreeMapNode<class_type>* node, List<const char*>* list=NULL) {

        if (list == NULL) {
          list = new List<const char*>();
        }

        if (node != NULL) {
          TreeMapNode<class_type>* leftChild = node->getLeft();
          TreeMapNode<class_type>* rightChild = node->getRight();

          this->getKeys(leftChild, list);
          this->getKeys(rightChild, list);

          list->push(node->getKey());
        }

        return list;
      }

      List<class_type>* getValues(TreeMapNode<class_type>* node, List<class_type>* list=NULL) {

        if (list == NULL) {
          list = new List<class_type>();
        }

        if (node != NULL) {
          TreeMapNode<class_type>* leftChild = node->getLeft();
          TreeMapNode<class_type>* rightChild = node->getRight();

          this->getValues(leftChild, list);
          this->getValues(rightChild, list);

          list->push(node->getValue());
        }

        return list;
      }




//      TreeMapNode<class_type>* getMinIndex(TreeMapNode<class_type>* node) {
//        TreeMapNode<class_type>* leftChild = node->getLeft();
//
//        if (leftChild == NULL) {
//          return node;
//        } else {
//          return this->getMinIndex(leftChild);
//        }
//
//      }
//
//      TreeMapNode<class_type>* getMaxIndex(TreeMapNode<class_type>* node) {
//        TreeMapNode<class_type>* rightChild = node->getLeft();
//
//        if (rightChild == NULL) {
//          return node;
//        } else {
//          return this->getMinIndex(rightChild);
//        }
//
//      }

//      void deleteEntry(const char* key) {
//        this->root = this->deleteEntry(this->root, key);
//        this->decrementIndices(this->root, key);
//      }
//
//      TreeMapNode<class_type>* deleteEntry(TreeMapNode<class_type>* node, const char* key) {
//
//        if (node == NULL) {
//          return node;    // maybe throw an exception??
//        }
//
//        if (key < node->getKey()) {
//          // move left...
//          TreeMapNode<class_type>* leftChild = node->getLeft();
//          TreeMapNode<class_type>* tmpNode = this->deleteEntry(leftChild, key);
//
//          node->setLeft(tmpNode);
//
//          return node;
//
//        } else if (key > node->getKey()) {
//          // move right...
//          TreeMapNode<class_type>* rightChild = node->getRight();
//          TreeMapNode<class_type>* tmpNode = this->deleteEntry(rightChild, key);
//
//          node->setRight(tmpNode);
//
//          return node;
//
//        } else {
//
//          //this->length--;
//
//          TreeMapNode<class_type>* leftChild = node->getLeft();
//          TreeMapNode<class_type>* rightChild = node->getRight();
//
//          if (leftChild == NULL && rightChild == NULL) {
//            // just delete the entry.
//            return NULL;
//
//          } else if (rightChild == NULL) {
//            // we have only a left child...promote it.
//            return leftChild;
//
//
//          } else if (leftChild == NULL) {
//            // we have only a right child...promote it.
//            return rightChild;
//
//
//          } else {
//            // we have two children...it gets a bit more complex.
//            TreeMapNode<class_type>* minNode = this->getMinIndex(rightChild);
//            minNode->setLeft(leftChild);
//            rightChild->setLeft(minNode);
//
//            return rightChild;
//          }
//
//
//        }
//
//        return node;
//      }

      TreeMapNode<class_type>* clear(TreeMapNode<class_type>* node) {

        if (node != NULL) {
          TreeMapNode<class_type>* leftChild = node->getLeft();
          TreeMapNode<class_type>* rightChild = node->getRight();

          TreeMapNode<class_type>* tmpLeft = this->clear(leftChild);
          TreeMapNode<class_type>* tmpRight = this->clear(rightChild);

          delete tmpLeft;
          delete tmpRight;

          node->setLeft(NULL);
          node->setRight(NULL);
        }

        return node;
      }


    public:

      TreeMap() {
        this->root = NULL;
      }

      ~TreeMap() {
        this->clear(this->root);

        delete this->root;
      }

      //TreeMapNode<class_type>* getRoot() {
      //  return this->root;
      //}

      class_type get(const char* key) {
        return this->getEntry(key);
      }

      void set(const char* key, class_type value) {
        this->setEntry(key, value);
      }

      //void remove(const char* key) {
      //  this->deleteEntry(key);
      //}

      bool has(const char* key) {
        return !!this->getEntry(key);
      }

      List<const char*>* getKeys() {
        return this->getKeys(this->root);
      }

      List<class_type>* getValues() {
        return this->getValues(this->root);
      }

  };


#endif
