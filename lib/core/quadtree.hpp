
#ifndef _QUADTREE_HPP

  #define _QUADTREE_HPP

  #include "./list.hpp"
  #include "./quadtree/element.hpp"


  template <class class_type>
  class Quadtree {

    public:

      float width;
      float height;

      List<Quadtree<class_type>*>* children;  // four cartesion quadrants
      List<QuadtreeElement<class_type>*>* elements;

      Quadtree(float width, float height) {
        this->width = width;
        this->height = height;

        this->children = new List<Quadtree<class_type>*>();
        this->elements = new List<QuadtreeElement<class_type>*>();

        uint32_t childWidth = this->width / 2;
        uint32_t childHeight = this->height / 2;
      }

      void insert(class_type newVal, float horzPos, float vertPos/*, float width, float height*/, uint8_t depth=0) {

        QuadtreeElement<class_type>* newEl = new QuadtreeElement<class_type>(horzPos, vertPos);
        newEl->value = newVal;

        this->elements->unshift(newEl);

        uint8_t quadNum = Quadtree::determineQuadrant(this, horzPos, vertPos);

        Quadtree<class_type>* child = this->children->get(quadNum);

        uint32_t quadWidth = this->width / 2;
        uint32_t quadHeight = this->height / 2;

        if (child == NULL) {
          child = new Quadtree<class_type>(quadWidth, quadHeight);

          this->children->set(quadNum, child);
        }

        if (quadWidth < 1 || quadHeight < 1) {
          return;
        }


        float childHorzPos = horzPos;
        float childVertPos = vertPos;

        if (quadNum == 0) {
          childHorzPos = horzPos - (this->width / 2);
          //childVertPos = vertPos;
        } /*else if (quadNum == 1) {
          //childHorzPos = horzPos;
          //childVertPos = vertPos;
        }*/ else if (quadNum == 2) {
          //childHorzPos = horzPos;
          childVertPos = vertPos - (this->height / 2);
        } else if (quadNum == 3) {
          childHorzPos = horzPos - (this->width / 2);
          childVertPos = vertPos - (this->height / 2);
        }

        child->insert(newVal, childHorzPos, childVertPos, depth + 1);

        return;
      }

      LinkedList<QuadtreeElement<class_type>*>* query(float horzPos, float vertPos/*, float width, float height*/, uint8_t depth=0) {

        uint8_t quadNum = Quadtree::determineQuadrant(this, horzPos, vertPos);

        Quadtree<class_type>* child = this->children->get(quadNum);

        if (child == NULL) {
          return new LinkedList<QuadtreeElement<class_type>*>();
        }

        if (child->width < 1 || child->height < 1) {
          return this->elements->clone();
        }

        float childHorzPos = horzPos;
        float childVertPos = vertPos;

        if (quadNum == 0) {
          childHorzPos = horzPos - (this->width / 2);
          //childVertPos = vertPos;
        } /*else if (quadNum == 1) {
          //childHorzPos = horzPos;
          //childVertPos = vertPos;
        }*/ else if (quadNum == 2) {
          //childHorzPos = horzPos;
          childVertPos = vertPos - (this->height / 2);
        } else if (quadNum == 3) {
          childHorzPos = horzPos - (this->width / 2);
          childVertPos = vertPos - (this->height / 2);
        }

        return child->query(childHorzPos, childVertPos, depth + 1);
      }

      static uint8_t determineQuadrant(Quadtree<class_type>* node, float horzPos, float vertPos) {
        uint8_t outp = 0;

        if (horzPos < (node->width / 2) && vertPos < (node->height / 2)) {
          outp = 1;

        } else if (horzPos < (node->width / 2) && vertPos > (node->height / 2)) {
          outp = 2;

        } /*else if (horzPos > (node->width / 2) && vertPos < (node->height / 2)) {
          outp = 0;

        }*/ else if (horzPos > (node->width / 2) && vertPos > (node->height / 2)) {
          outp = 3;
        }

        return outp;
      }

  };

#endif
