

#ifndef _TREE_LIST_HPP

  #define _TREE_LIST_HPP

  #include <stdio.h>
  #include <stdint.h>
  #include "./tree_list/node.hpp"


  template <class class_type>
  class TreeList {
    // TODO: Optimize this...it's SLOOOW!!


    private:

      TreeListNode<class_type>* root;

      uint32_t length;

      class_type getEntry(uint32_t targIndex) {
        TreeListNode<class_type>* node = getEntry(this->root, targIndex);

        if (node != NULL) {
          return node->getValue();
        }

        return NULL;
      }

      TreeListNode<class_type>* getEntry(TreeListNode<class_type>* node, uint32_t targIndex) {

        if (node == NULL) {
          return NULL;
        }

        if (node->getIndex() == targIndex) {
          return node;
        }

        TreeListNode<class_type>* left = getEntry(node->getLeft(), targIndex);
        TreeListNode<class_type>* right = getEntry(node->getRight(), targIndex);

        if (left) {
          return left;
        } else {
          return right;
        }

      }

      void setEntry(uint32_t targIndex, class_type value) {
        this->setEntry(this->root, targIndex, value);
      }

      void setEntry(TreeListNode<class_type>* node, uint32_t targIndex, class_type value) {

        if (this->length == 0) {
          this->root = new TreeListNode<class_type>();

          this->root->setIndex(targIndex);
          this->root->setValue(value);

          this->length++;

          return;
        }

        if (targIndex < node->getIndex()) {
          TreeListNode<class_type>* leftNode = node->getLeft();

          if (leftNode == NULL) {
            TreeListNode<class_type>* newNode = new TreeListNode<class_type>();
            newNode->setIndex(targIndex);
            newNode->setValue(value);

            node->setLeft(newNode);

            this->length++;

          } else {
            this->setEntry(leftNode, targIndex, value);
          }

        } else if (targIndex > node->getIndex()) {
          TreeListNode<class_type>* rightNode = node->getRight();

          if (rightNode == NULL) {
            TreeListNode<class_type>* newNode = new TreeListNode<class_type>();
            newNode->setIndex(targIndex);
            newNode->setValue(value);

            node->setRight(newNode);

            this->length++;

          } else {
            this->setEntry(rightNode, targIndex, value);
          }

        } else {
          node->setValue(value);
        }

      }

      void insertEntry(uint32_t targIndex, class_type value) {
        this->incrementIndices(this->root, targIndex);
        this->setEntry(this->root, targIndex, value);
      }

      void incrementIndices(TreeListNode<class_type>* node, uint32_t targIndex) {

        if (this->length == 0) {
          return;
        }

        uint32_t nodeIndex = node->getIndex();

        if (nodeIndex >= targIndex) {
          node->setIndex(nodeIndex + 1);
        }

        TreeListNode<class_type>* leftChild = node->getLeft();
        TreeListNode<class_type>* rightChild = node->getRight();

        if (leftChild != NULL) {
          this->incrementIndices(leftChild, targIndex);
        }

        if (rightChild != NULL) {
          this->incrementIndices(rightChild, targIndex);
        }

      }

      void decrementIndices(TreeListNode<class_type>* node, uint32_t targIndex) {

        if (this->length == 0) {
          return;
        }

        uint32_t nodeIndex = node->getIndex();

        if (nodeIndex > targIndex) {
          node->setIndex(nodeIndex - 1);
        }

        TreeListNode<class_type>* leftChild = node->getLeft();
        TreeListNode<class_type>* rightChild = node->getRight();

        if (leftChild != NULL) {
          this->decrementIndices(leftChild, targIndex);
        }

        if (rightChild != NULL) {
          this->decrementIndices(rightChild, targIndex);
        }

      }

      TreeListNode<class_type>* getMinIndex(TreeListNode<class_type>* node) {
        TreeListNode<class_type>* leftChild = node->getLeft();

        if (leftChild == NULL) {
          return node;
        } else {
          return this->getMinIndex(leftChild);
        }

      }

      TreeListNode<class_type>* getMaxIndex(TreeListNode<class_type>* node) {
        TreeListNode<class_type>* rightChild = node->getLeft();

        if (rightChild == NULL) {
          return node;
        } else {
          return this->getMinIndex(rightChild);
        }

      }

      void deleteEntry(uint32_t targIndex) {
        this->root = this->deleteEntry(this->root, targIndex);

        this->decrementIndices(this->root, targIndex);
      }

      TreeListNode<class_type>* deleteEntry(TreeListNode<class_type>* node, uint32_t targIndex) {
        // TODO: this!!!!
        if (node == NULL) {
          return node;    // maybe throw an exception??
        }

        TreeListNode<class_type>* leftChild = node->getLeft();
        TreeListNode<class_type>* rightChild = node->getRight();

        if (targIndex < node->getIndex()) {
          // move left...
          TreeListNode<class_type>* tmpNode = this->deleteEntry(leftChild, targIndex);

          node->setLeft(tmpNode);

          return node;

        } else if (targIndex > node->getIndex()) {
          // move right...
          TreeListNode<class_type>* tmpNode = this->deleteEntry(rightChild, targIndex);

          node->setRight(tmpNode);

          return node;

        } else {

          this->length--;

          TreeListNode<class_type>* leftChild = node->getLeft();
          TreeListNode<class_type>* rightChild = node->getRight();

          if (leftChild == NULL && rightChild == NULL) {
            // just delete the entry.
            return NULL;

          } else if (rightChild == NULL) {
            // we have only a left child...promote it.
            return leftChild;


          } else if (leftChild == NULL) {
            // we have only a right child...promote it.
            return rightChild;


          } else {
            // we have two children...it gets a bit more complex.
            TreeListNode<class_type>* minNode = this->getMinIndex(rightChild);
            minNode->setLeft(leftChild);
            rightChild->setLeft(minNode);

            return rightChild;
          }


        }

        return node;
      }


    public:

      TreeList() {
        this->root = NULL;
        this->length = 0;
      }

      TreeListNode<class_type>* getRoot() {
        return this->root;
      }

      uint32_t getLength() {
        return this->length;
      }

      class_type get(uint32_t targIndex) {
        return this->getEntry(targIndex);
      }

      void set(uint32_t targIndex, class_type value) {
        this->setEntry(targIndex, value);
      }

      void remove(uint32_t targIndex) {
        this->deleteEntry(targIndex);
      }

      void push(class_type value) {
        this->insertEntry(this->length, value);
      }

      void unshift(class_type value) {
        this->insertEntry(0, value);
      }

      class_type pop() {
        uint32_t index = this->getLength() - 1;
        class_type val = this->getEntry(index);

        this->deleteEntry(index);

        return val;
      }

      class_type shift() {
        class_type val = this->getEntry(0);

        this->deleteEntry(0);

        return val;
      }

      //void fill(class_type value, uint32_t end=0, uint32_t start=0) {
      //}

  };


#endif
