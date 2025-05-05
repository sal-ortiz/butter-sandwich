
#ifndef _BINARY_TREE_LIST

  #define _BINARY_TREE_LIST

  //#include <stdio.h>
  #include <stddef.h>

  #include <core/list/list.hpp>
  #include <core/list/node/binary_tree_list_node.hpp>


  template <class class_type>
  class BinaryTreeList: public List<class_type> {

    private:

      BinaryTreeListNode<class_type>* root;

      uint32_t length;


      BinaryTreeListNode<class_type>* getEntry(uint32_t targIndex) override {

        if (this->root == NULL) {
          return NULL;
        }

        BinaryTreeListNode<class_type>* curNode = this->root;
        uint32_t curIndex = curNode->index;

        while (curNode != NULL && curIndex != targIndex) {
          curIndex = curNode->index;

          if (targIndex < curIndex) {
            curNode = curNode->left;
          } else if (targIndex > curIndex) {
            curNode = curNode->right;
          }

          if (curNode == NULL) {
            return NULL;
          }

          curIndex = curNode->index;
        }

        return curNode;
      }

      void setEntry(uint32_t targIndex, class_type value) {

        if (targIndex >= this->length) {
          this->length = targIndex + 1;
        }

        if (this->root == NULL) {
          this->root = new BinaryTreeListNode<class_type>();

          this->root->index = targIndex;
          this->root->value = value;

          return;
        }

        BinaryTreeListNode<class_type>* prevNode = NULL;
        BinaryTreeListNode<class_type>* curNode = this->root;

        while (curNode != NULL) {
          uint32_t curNodeIdx = curNode->index;

          if (targIndex == curNodeIdx) {
            curNode->value = value;

            return;
          }

          if (targIndex < curNodeIdx) {
            prevNode = curNode;
            curNode = curNode->left;

          } else if (targIndex > curNode->index) {
            prevNode = curNode;
            curNode = curNode->right;
          }

        }

        uint32_t prevNodeIdx = prevNode->index;

        BinaryTreeListNode<class_type>* newNode = new BinaryTreeListNode<class_type>();

        newNode->index = targIndex;
        newNode->value = value;

        //newNode->left = NULL;
        //newNode->right = NULL;

        if (targIndex < prevNodeIdx) {
          prevNode->left = newNode;
        } else if (targIndex > prevNodeIdx) {
          prevNode->right = newNode;
        }

      }

      void insertEntry(uint32_t targIndex, class_type value) override {
        BinaryTreeListNode<class_type>* node = this->root;

        this->insertEntry(node, targIndex, value);
        this->setEntry(targIndex, value);

        this->length++;
      }

      void insertEntry(BinaryTreeListNode<class_type>* node, uint32_t targIndex, class_type value) {

        if (node == NULL) {
          return;
        }

        uint32_t nodeIdx = node->index;

        if (nodeIdx >= targIndex) {
          node->index = nodeIdx + 1;
        }

        BinaryTreeListNode<class_type>* leftChild = node->left;
        BinaryTreeListNode<class_type>* rightChild = node->right;

        this->insertEntry(leftChild, targIndex, value);
        this->insertEntry(rightChild, targIndex, value);
      }

      void deleteEntry(uint32_t targIndex) override {
          this->root = this->deleteEntryWorker(targIndex, this->root);
      }

      BinaryTreeListNode<class_type>* deleteEntryWorker(uint32_t targIndex, BinaryTreeListNode<class_type>* curNode=NULL) {

        if (targIndex < curNode->index) {
          curNode->left = this->deleteEntryWorker(targIndex, curNode->left);

          return curNode;

        } else if (targIndex > curNode->index) {
          curNode->right = this->deleteEntryWorker(targIndex, curNode->right);

          return curNode;

        } else {

          this->length--;

          if (!curNode->left && !curNode->right) {
            delete curNode;

            return NULL;

          } else if (curNode->left && !curNode->right) {
            BinaryTreeListNode<class_type>* leftNode = curNode->left;

            delete curNode;
            return leftNode;

          } else if (!curNode->left && curNode->right) {
            BinaryTreeListNode<class_type>* rightNode = curNode->right;

            delete curNode;
            return rightNode;

          } else if (curNode->left && curNode->right) {
            BinaryTreeListNode<class_type>* newNode = curNode->right;

            while (newNode->left != NULL) {
              newNode = newNode->left;
            }

            //// TODO: what happens if newNode has a right child??
            if (newNode->right != NULL) {
              newNode = newNode->right;
            }

            //newNode->right = curNode->right;

            delete curNode;

            return newNode;
          }

        }

        return NULL;
      }

      static void emptyList(BinaryTreeListNode<class_type>* node) {

        if (node->left != NULL) {
          BinaryTreeList::emptyList(node->left);

          delete node->left;
        }

        if (node->right != NULL) {
          BinaryTreeList::emptyList(node->right);

          delete node->right;
        }

      }


    public:

      BinaryTreeList() {
        this->root = NULL;
        this->length = 0;
      }

      ~BinaryTreeList() {

        if (this->root != NULL) {
          this->emptyList(this->root);

          delete this->root;
        }

        this->length = 0;
      }

      uint32_t getLength() {
        return this->length;
      }

      class_type get(uint32_t targIndex) {
        BinaryTreeListNode<class_type>* node = this->getEntry(targIndex);

        if (node != NULL) {
          return node->value;
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
        class_type value = entry->value;

        this->deleteEntry(index);

        return value;
      }

      class_type shift() {
        uint32_t index = 0;

        BinaryTreeListNode<class_type>* entry = this->getEntry(index);

        this->deleteEntry(index);

        return entry->value;
      }

      void unshift(class_type value) {
        this->insertEntry(0, value);
      }

  };

#endif
