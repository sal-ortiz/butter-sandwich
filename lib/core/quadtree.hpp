
#ifndef _QUADTREE_HPP

  #define _QUADTREE_HPP

  #include <core/list/linked_list.hpp>
  #include <core/quadtree/node.hpp>
  #include <core/quadtree/element.hpp>


  #define _QUADTREE_MAX_DEPTH     16


  template <class class_type>
  class Quadtree {

    public:

      float width;
      float height;

      LinkedList<QuadtreeElement<class_type>*>* elements;

      QuadtreeNode<class_type>* tree;

      Quadtree(float width, float height) {
        this->width = width;
        this->height = height;

        this->tree = new QuadtreeNode<class_type>(0, 0, width, height);
      }

      ~Quadtree() {
        this->emptyTree(this->tree);

        delete this->tree;
      }

      static void emptyTree(QuadtreeNode<class_type>* node) {

        for (uint8_t idx = 0; idx < 4; idx++) {
          QuadtreeNode<class_type>* child = node->children[idx];

          if (child != NULL) {
            Quadtree::emptyTree(child);

            delete child;
          }

        }

      }

      void insert(uint32_t xPos, uint32_t yPos, uint32_t width, uint32_t height, class_type val) {

        QuadtreeNode<class_type>* node = this->tree;
        QuadtreeNode<class_type>* prev;

        uint32_t depth = 0;

        while (depth < _QUADTREE_MAX_DEPTH) {

          if (node == NULL) {
            uint8_t quadNum = Quadtree::calculateQuadrant(prev, xPos, yPos);

            uint32_t newNodeHorzPos = prev->xPos;
            uint32_t newNodeVertPos = prev->yPos;

            float newNodeWidth = prev->width / 2;
            float newNodeHeight = prev->height / 2;

            if (quadNum == 0) {
              newNodeHorzPos += newNodeWidth;
            }

            if (quadNum == 2) {
              newNodeVertPos += newNodeHeight;
            }

            if (quadNum == 3) {
              newNodeHorzPos += newNodeWidth;
              newNodeVertPos += newNodeHeight;
            }

            QuadtreeNode<class_type>* newNode = new QuadtreeNode<class_type>(newNodeHorzPos, newNodeVertPos, newNodeWidth, newNodeHeight);

            prev->children[quadNum] = newNode;
            node = newNode;
          }

          uint8_t quadNum = Quadtree::calculateQuadrant(node, xPos, yPos);

          node->addElement(xPos, yPos, width, height, val);

          prev = node;
          node = node->children[quadNum];

          depth++;
        }

      }

      LinkedList<QuadtreeElement<class_type>*>* query(uint32_t xPos, uint32_t yPos, uint32_t width, uint32_t height) {

        QuadtreeNode<class_type>* prev = NULL;
        QuadtreeNode<class_type>* node = this->tree;

        while (node != NULL) {
          uint8_t quadNum = Quadtree::calculateQuadrant(node, xPos, yPos);

          prev = node;
          node = node->children[quadNum];
        }

        return prev->elements->clone();  // maybe clone this list?
      }

      static uint8_t calculateQuadrant(QuadtreeNode<class_type>* node, uint32_t xPos, uint32_t yPos) {
        uint8_t quadNum = 1;

        uint32_t quadWidth = node->width / 2;
        uint32_t quadHeight = node->height / 2;

        float adjHorzPos = xPos - node->xPos;
        float adjVertPos = yPos - node->yPos;

        if (adjHorzPos > quadWidth) {

          if (adjVertPos > quadHeight) {
            quadNum = 3;
          } else {
            quadNum = 0;
          }

        } else {

          if (adjVertPos > quadHeight) {
            quadNum = 2;
          }/* else {
            quadNum = 1;
          }*/

        }

        return quadNum;
      }

  };

#endif
