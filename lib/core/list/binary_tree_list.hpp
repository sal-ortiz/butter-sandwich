

#ifndef _BINARY_TREE_LIST

  #define _BINARY_TREE_LIST

  //#include <stdio.h>
  #include <stddef.h>
  #include "binary_tree_list/node.hpp"




  template <class class_type>
  class BinaryTreeList {

    private:

      BinaryTreeListNode<class_type>* root;

      uint32_t length;


      BinaryTreeListNode<class_type>* getEntry(uint32_t targIndex) {

        if (this->root == NULL) {
          return NULL;
        }

        BinaryTreeListNode<class_type>* curNode = this->root;
        uint32_t curIndex = curNode->getIndex();

        while (curNode != NULL && curIndex != targIndex) {
          curIndex = curNode->getIndex();

          if (targIndex < curIndex) {
            curNode = curNode->getLeft();
          } else if (targIndex > curIndex) {
            curNode = curNode->getRight();
          }

          if (curNode == NULL) {
            return NULL;
          }

          curIndex = curNode->getIndex();
        }

        return curNode;
      }

      void setEntry(uint32_t targIndex, class_type value) {

        if (targIndex >= this->length) {
          this->length = targIndex + 1;
        }

        if (this->root == NULL) {
          this->root = new BinaryTreeListNode<class_type>();

          this->root->setIndex(targIndex);
          this->root->setValue(value);

          return;
        }

        BinaryTreeListNode<class_type>* prevNode = NULL;
        BinaryTreeListNode<class_type>* curNode = this->root;

        while (curNode != NULL) {
          uint32_t curNodeIdx = curNode->getIndex();

          if (targIndex == curNodeIdx) {
            curNode->setValue(value);

            return;
          }

          if (targIndex < curNodeIdx) {
            prevNode = curNode;
            curNode = curNode->getLeft();

          } else if (targIndex > curNode->getIndex()) {
            prevNode = curNode;
            curNode = curNode->getRight();

          }

        }

        uint32_t prevNodeIdx = prevNode->getIndex();

        if (targIndex < prevNodeIdx) {
          BinaryTreeListNode<class_type>* newNode = new BinaryTreeListNode<class_type>();

          newNode->setIndex(targIndex);
          newNode->setValue(value);

          prevNode->setLeft(newNode);

        } else if (targIndex > prevNodeIdx) {
          BinaryTreeListNode<class_type>* newNode = new BinaryTreeListNode<class_type>();

          newNode->setIndex(targIndex);
          newNode->setValue(value);

          prevNode->setRight(newNode);
        }

      }

      void insertEntry(uint32_t targIndex, class_type value) {
        BinaryTreeListNode<class_type>* node = this->root;

        this->insertEntry(node, targIndex, value);
        this->setEntry(targIndex, value);

        this->length++;
      }

      void insertEntry(BinaryTreeListNode<class_type>* node, uint32_t targIndex, class_type value) {

        if (node == NULL) {
          return;
        }


        uint32_t nodeIdx = node->getIndex();

        if (nodeIdx >= targIndex) {
          node->setIndex(nodeIdx + 1);
        }

        BinaryTreeListNode<class_type>* leftChild = node->getLeft();
        BinaryTreeListNode<class_type>* rightChild = node->getRight();

        this->insertEntry(leftChild, targIndex, value);
        this->insertEntry(rightChild, targIndex, value);
      }


      void deleteEntry(uint32_t targIndex) {
        BinaryTreeListNode<class_type>* node = this->root;

        this->root = this->deleteEntry(node, targIndex);

        this->length--;
      }

      BinaryTreeListNode<class_type>* deleteEntry(BinaryTreeListNode<class_type>* node, uint32_t targIndex) {

        if (node == NULL) {
          return NULL;
        }

        BinaryTreeListNode<class_type>* leftChild = node->getLeft();
        BinaryTreeListNode<class_type>* rightChild = node->getRight();

        leftChild = this->deleteEntry(leftChild, targIndex);
        rightChild = this->deleteEntry(rightChild, targIndex);

        uint32_t nodeIndex = node->getIndex();

        if (nodeIndex == targIndex) {

          if (!leftChild && !rightChild) {
            return NULL;
          } else if (!leftChild && rightChild) {
            return rightChild;
          } else if (leftChild && !rightChild) {
            return leftChild;
          } else {

            BinaryTreeListNode<class_type>* prev = node;
            BinaryTreeListNode<class_type>* succ = rightChild;

            while (succ->getLeft() != NULL) {
              prev = succ;
              succ = succ->getLeft();
            }

            BinaryTreeListNode<class_type>* newLeaf = succ->getRight();

            prev->setLeft(newLeaf);

            succ->setLeft(leftChild);
            succ->setRight(rightChild);

            delete node;

            return succ;
          }

        } else if (nodeIndex > targIndex) {
          node->setIndex(nodeIndex - 1);
        }

        return node;
      }


    public:


      BinaryTreeList() {
        this->root = NULL;
        this->length = 0;
      }

      //~StaticTreeList() {
      //
      //}

      uint32_t getLength() {
        return this->length;
      }

      class_type get(uint32_t targIndex) {
        BinaryTreeListNode<class_type>* node = this->getEntry(targIndex);

        if (node != NULL) {
          return node->getValue();
        }

        return (class_type)NULL;
      }

      void set(uint32_t targIndex, class_type value) {
        this->setEntry(targIndex, value);
      }

      void push(class_type value) {
        uint32_t index = this->length;

        this->setEntry(index, value);
      }

      class_type pop() {
        uint32_t index = this->length - 1;

        BinaryTreeListNode<class_type>* entry = this->getEntry(index);

        this->deleteEntry(index);

        return entry->getValue();
      }

      class_type shift() {
        uint32_t index = 0;

        BinaryTreeListNode<class_type>* entry = this->getEntry(index);

        this->deleteEntry(index);

        return entry->getValue();
      }

      void unshift(class_type value) {
        this->insertEntry(0, value);
      }

  };

#endif
