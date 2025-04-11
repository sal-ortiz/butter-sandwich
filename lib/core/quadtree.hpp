
#ifndef _QUADTREE_HPP

  #define _QUADTREE_HPP

  #include "./list/list.hpp"
  #include "./quadtree/element.hpp"


  #define _QUADTREE_MAX_DEPTH     18

  template <class class_type>
  class Quadtree {

    public:

      float width;
      float height;

      uint32_t xPos;
      uint32_t yPos;

      Quadtree<class_type>* children[4];    // four cartesian quadrants
      LinkedList<QuadtreeElement<class_type>*>* elements;

      Quadtree(float width, float height) {
        this->width = width;
        this->height = height;

        this->children[0] = NULL;   // upper-right
        this->children[1] = NULL;   // upper-left
        this->children[2] = NULL;   // lower-left
        this->children[3] = NULL;   // lower-right

        this->elements = new LinkedList<QuadtreeElement<class_type>*>();
      }

      void insert(uint32_t xPos, uint32_t yPos, uint32_t width, uint32_t height, class_type val, uint16_t depth=0) {

        if (depth > _QUADTREE_MAX_DEPTH) {
          return;
        }

        QuadtreeElement<class_type>* newEl = new QuadtreeElement<class_type>();

        newEl->horzPos = xPos;
        newEl->vertPos = yPos;
        newEl->width = width;
        newEl->height = height;
        newEl->value = val;

        this->elements->push(newEl);
        //this->elements->unshift(newEl);

        uint8_t quadNum = this->calculateQuadrant(xPos, yPos);

        Quadtree<class_type>* child = this->children[quadNum];

        if (!child) {
          float childWidth = this->width / 2;
          float childHeight = this->height / 2;

          child = new Quadtree<class_type>(childWidth, childHeight);
        }

        if ((child->width > width && child->height > height) || this->elements->getLength() > 1) {
          child->insert(xPos, yPos, width, height, val, depth + 1);
        }

        this->children[quadNum] = child;
      }

      LinkedList<QuadtreeElement<class_type>*>* query(uint32_t xPos, uint32_t yPos, uint32_t width, uint32_t height) {
        uint8_t quadNum = this->calculateQuadrant(xPos, yPos);

        Quadtree<class_type>* child = this->children[quadNum];

        if (!child || child->elements->getLength() < 2) {
          return this->elements;
        }

        return child->query(xPos, yPos, width, height);
      }

      uint8_t calculateQuadrant(uint32_t xPos, uint32_t yPos) {
        uint8_t quadNum = 1;

        if (xPos > (this->width / 2)) {

          if (yPos > (this->height / 2)) {
            quadNum = 3;
          } else {
            quadNum = 0;
          }

        } else {

          if (yPos > (this->height / 2)) {
            quadNum = 2;
          }/* else {
            quadNum = 1;
          }*/

        }

        return quadNum;
      }

  };

#endif
