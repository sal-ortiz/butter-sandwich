
#ifndef _QUADTREE_HPP

  #define _QUADTREE_HPP

  #include "./list.hpp"
  #include "./quadtree/element.hpp"


  template <class class_type>
  class Quadtree {

    public:

      float width;
      float height;

      uint32_t xPos;
      uint32_t yPos;


      Quadtree<class_type>* children[4];    // four cartesian quadrants
      LinkedList<QuadtreeElement<class_type>*>* elements;

      Quadtree(float width, float height, uint32_t xPos, uint32_t yPos) {
        this->width = width;
        this->height = height;

        this->xPos = xPos;
        this->yPos = yPos;

        this->children[0] = NULL;   // upper-right
        this->children[1] = NULL;   // upper-left
        this->children[2] = NULL;   // lower-left
        this->children[3] = NULL;   // lower-right

        this->elements = new LinkedList<QuadtreeElement<class_type>*>();
      }

      void insert(uint32_t xPos, uint32_t yPos, uint32_t width, uint32_t height, class_type val, uint16_t depth=0) {
        uint8_t quadNum = this->calculateQuadrant(xPos, yPos);
        Quadtree<class_type>* child = this->children[quadNum];

        QuadtreeElement<class_type>* newEl = new QuadtreeElement<class_type>();

        newEl->horzPos = xPos;
        newEl->vertPos = yPos;
        newEl->width = width;
        newEl->height = height;
        newEl->value = val;

        this->elements->push(newEl);

        if (!child) {
          float childWidth = this->width / 2;
          float childHeight = this->height / 2;
          uint32_t childHorzPos = this->xPos;
          uint32_t childVertPos = this->yPos;

          if ((xPos - this->xPos) > childWidth) {
            childHorzPos += childWidth;
          }

          if ((yPos - this->yPos) > childHeight) {
            childVertPos += childHeight;
          }

          child = new Quadtree<class_type>(childWidth, childHeight, childHorzPos, childVertPos);
        }

        if (child->width > 1 && child->height > 1) {
          child->insert(xPos, yPos, width, height, val, depth + 1);
        }

        this->children[quadNum] = child;
      }

      LinkedList<QuadtreeElement<class_type>*>* query(uint32_t xPos, uint32_t yPos, uint32_t width, uint32_t height, uint16_t depth=0) {
        uint8_t quadNum = this->calculateQuadrant(xPos, yPos);

        Quadtree<class_type>* child = this->children[quadNum];

        if (!child) {
          // TODO: maybe return NULL instead of creating a new object.
          return new LinkedList<QuadtreeElement<class_type>*>();
        }

        if (
          ((xPos - this->xPos) + width > this->width)
          && ((yPos - this->yPos) + height > this->height)
        ) {
          // TODO: maybe clone this->elements to avoid breaking our list.
          return this->elements;
        }


        return child->query(xPos, yPos, width, height, depth + 1);
      }

      uint8_t calculateQuadrant(uint32_t xPos, uint32_t yPos) {
        uint8_t quadNum = 1;

        if ((xPos - this->xPos) > (this->width / 2)) {

          if ((yPos - this->yPos) > (this->height / 2)) {
            quadNum = 3;
          } else {
            quadNum = 0;
          }

        } else {

          if ((yPos - this->yPos) > (this->height / 2)) {
            quadNum = 2;
          }/* else {
            quadNum = 1;
          }*/

        }

        return quadNum;
      }

  };

#endif
