
#ifndef _FIXED_TREE_LIST_HPP

  #define _FIXED_TREE_LIST_HPP

  #include <stdint.h>

  #include "fixed_tree_list/node.hpp"


  template <class class_type>
  class FixedTreeList {

    private:

      FixedTreeListNode<class_type>* root;

      uint32_t length;

      FixedTreeListNode<class_type>* getEntry(uint32_t targIndex) {
        FixedTreeListNode<class_type>* curNode = this->root;

        uint32_t targLevelNum = log2(targIndex + 1);

        uint32_t curLevelMin = pow(2, targLevelNum);
        uint32_t curLevelMax = curLevelMin * 2;

        for (uint8_t lvl = 0; lvl < targLevelNum; lvl++) {
          uint32_t curLevelWidth = curLevelMax - curLevelMin;

          if (targIndex < curLevelMin + (curLevelWidth / 2) - 1) {
            // go left
            curNode = curNode->left;

            curLevelMax = curLevelMax - (curLevelWidth / 2);

          } else {
            // go right
            curNode = curNode->right;

            curLevelMin = curLevelMin + (curLevelWidth / 2);
          }

          if (curNode == NULL) {
            return NULL;
          }

        }

        return curNode;
      }

      void setEntry(uint32_t targIndex, class_type value) {
        FixedTreeListNode<class_type>* curNode = this->root;
        uint32_t curIndex = 0;

        uint32_t targLevelNum = log2(targIndex + 1);

        uint32_t curLevelMin = pow(2, targLevelNum);
        uint32_t curLevelMax = curLevelMin * 2;

        while (curIndex < targIndex) {
          uint32_t curLevelWidth = curLevelMax - curLevelMin;

          uint32_t childIdx;
          FixedTreeListNode<class_type>* child;

          if (targIndex < (curLevelMin + curLevelWidth / 2) - 1) {
            // go left
            child = curNode->left;
            childIdx = (curIndex * 2) + 1;

            if (child == NULL) {
              child = new FixedTreeListNode<class_type>();

              curNode->left = child;
            }

            curLevelMax = curLevelMax - (curLevelWidth / 2);

          } else {
            // go right
            child = curNode->right;
            childIdx = (curIndex * 2) + 2;

            if (child == NULL) {
              child = new FixedTreeListNode<class_type>();

              curNode->right = child;
            }

            curLevelMin = curLevelMin + (curLevelWidth / 2);
          }

          curIndex = childIdx;
          curNode = child;
        }

        curNode->value = value;

        if (targIndex >= this->length) {
          this->length = targIndex + 1;
        }

      }

      void insertEntry(uint32_t targIndex, class_type value) {
        // TODO: FIND A WAY TO OPTIMIZE THIS!!!1


        if (targIndex >= this->length) {
          this->setEntry(targIndex, value);

          return;
        }

        for (uint32_t idx = this->length - 1; idx > targIndex; idx--) {
          FixedTreeListNode<class_type>* curNode = this->getEntry(idx);

          if (curNode != NULL) {
            this->setEntry(idx + 1, curNode->value);

            this->setEntry(idx, NULL);
          }

        }

        FixedTreeListNode<class_type>* lastNode = this->getEntry(targIndex);

        this->setEntry(targIndex + 1, lastNode->value);
        this->setEntry(targIndex, value);
      }

      void deleteEntry(uint32_t targIndex) {
        // TODO: FIND A WAY TO OPTIMIZE THIS!!!1

        if (targIndex >= this->length) {
          return;
        }

        for (uint32_t idx = targIndex; idx < this->length; idx++) {
          FixedTreeListNode<class_type>* curNode = this->getEntry(idx + 1);

          if (curNode != NULL) {
            this->setEntry(idx, curNode->value);
          }

        }

        this->setEntry(this->length - 1, NULL);
        this->length--;

      }


    public:

      FixedTreeList() {
        this->root = new FixedTreeListNode<class_type>();
        this->length = 0;
      }

      //~FixedTreeList() {
      //
      //}

      uint32_t getLength() {
        return this->length;
      }

      class_type get(uint32_t targIndex) {
        FixedTreeListNode<class_type>* node = this->getEntry(targIndex);

        if (node != NULL) {
          return node->value;
        }

        return (class_type)NULL;
      }

      void set(uint32_t targIndex, class_type value) {
        this->setEntry(targIndex, value);
      }

      void remove(uint32_t targIndex) {
        this->deleteEntry(targIndex);
      }

      void push(class_type value) {
        uint32_t index = this->length;

        this->setEntry(index, value);
      }

      void unshift(class_type value) {
        uint32_t index = 0;

        this->insertEntry(index, value);
      }

      class_type pop() {
        uint32_t index = this->length - 1;

        FixedTreeListNode<class_type>* node = this->getEntry(index);

        if (node == NULL) {
          return NULL;
        }

        class_type outpValue = node->value;

        this->deleteEntry(index);

        return outpValue;
      }

      class_type shift() {
        uint32_t index = 0;

        FixedTreeListNode<class_type>* node = this->getEntry(index);

        if (node == NULL) {
          return NULL;
        }

        class_type outpValue = node->value;

        this->deleteEntry(index);

        return outpValue;
      }

      //void fill(class_type value) {
      //
      //}

  };

#endif
