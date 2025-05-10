
#ifndef _QUADTREE_NODE_HPP

  #define _QUADTREE_NODE_HPP

  #include <core/list/linked_list.hpp>
  #include <core/quadtree/element.hpp>

  template <class class_type>
  class QuadtreeNode {

    public:

      float width;
      float height;

      uint32_t xPos;
      uint32_t yPos;

      QuadtreeNode<class_type>* children[4];    // four cartesian quadrants
      LinkedList<QuadtreeElement<class_type>*>* elements;

      QuadtreeNode(uint32_t xPos, uint32_t yPos, float width, float height) {
        this->xPos = xPos;
        this->yPos = yPos;
        this->width = width;
        this->height = height;

        this->children[0] = NULL;   // upper-right
        this->children[1] = NULL;   // upper-left
        this->children[2] = NULL;   // lower-left
        this->children[3] = NULL;   // lower-right

        this->elements = new LinkedList<QuadtreeElement<class_type>*>();
      }


      ~QuadtreeNode() {
        uint32_t numEls = this->elements->getLength();

        for (uint32_t elIdx = 0; elIdx < numEls; elIdx++) {
          QuadtreeElement<class_type>* el = this->elements->get(elIdx);

          delete el;
        }

        delete this->elements;
      }

      void addElement(uint32_t xPos, uint32_t yPos, uint32_t width, uint32_t height, class_type val) {
        QuadtreeElement<class_type>* newEl = new QuadtreeElement<class_type>();

        newEl->horzPos = xPos;
        newEl->vertPos = yPos;
        newEl->width = width;
        newEl->height = height;
        newEl->value = val;

        this->elements->push(newEl);
        //this->elements->unshift(newEl);
      }

  };

#endif
