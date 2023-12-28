
#ifndef _COLLISION_TREE_HPP

  #define _COLLISION_TREE_HPP

  #include <stdint.h>

  #include "./list.hpp"


  struct QuadNodeEntry {
    uint32_t horzPos;
    uint32_t vertPos;
    uint32_t width;
    uint32_t height;

    void*(*callback)(void*, void*, void*);
  };


  class QuadNode {

    public:

      List<QuadNodeEntry*>* elements;
      List<QuadNode*>* children;

      uint32_t vertPos;
      uint32_t horzPos;
      uint32_t width;
      uint32_t height;


      QuadNode(uint32_t width, uint32_t height, uint32_t horzPos=0, uint32_t vertPos=0) {
        this->width = width;
        this->height = height;
        this->horzPos = horzPos;
        this->vertPos = vertPos;

        this->elements = new List<QuadNodeEntry*>();
        this->children = new List<QuadNode*>();

        this->children->set(0, NULL);  // upper-right
        this->children->set(1, NULL);  // upper-left
        this->children->set(2, NULL);  // lower-left
        this->children->set(3, NULL);  // lower-right
      }

      ~QuadNode() {
        delete this->children->get(0);
        delete this->children->get(1);
        delete this->children->get(2);
        delete this->children->get(3);
      }

      void insert(uint32_t elHorzPos, uint32_t elVertPos, uint32_t elWidth, uint32_t elHeight, void*(*elCallback)(void*, void*, void*)) {

        //if (
        //  // check that our upper and left edges are within this quad.
        //  elHorzPos > this->horzPos && elVertPos > this->vertPos &&
        //  elHorzPos < this->horzPos + this->width &&
        //  elVertPos < this->vertPos + this->height
        //) {
          // our element's upper-left border is within this node
          QuadNodeEntry* newEntry = new QuadNodeEntry();

          newEntry->horzPos = elHorzPos;
          newEntry->vertPos = elVertPos;
          newEntry->width = elWidth;
          newEntry->height = elHeight;

          newEntry->callback = elCallback;

          this->elements->push(newEntry);

          List<unsigned char>* targNodeIndices = new List<unsigned char>();

          // start calculating which child nodes we'll be passing our element to.
          if (elHorzPos < this->horzPos + this->width / 2) {

            if (elVertPos < this->vertPos + this->height / 2) {
              // our element's upper-left edge is in ou upper-left quadrant.
              targNodeIndices->push(1);

              if (elHorzPos + elWidth > this->horzPos + this->width / 2) {
                // our elements's right edge is in another child node.
                targNodeIndices->push(0);
              }

              if (elVertPos + elHeight > this->vertPos + this->height / 2) {
                // our elements's bottom edge is in another child node.
                targNodeIndices->push(2);
              }

            } else {
              // our element's upper-left edge is in our upper-right quadrant.
              targNodeIndices->push(0);

              if (elVertPos + elHeight > this->vertPos + this->height / 2) {
                // our elements's bottom edge is in another child node.
                targNodeIndices->push(2);
              }

            }

          } else {

            if (elVertPos < this->vertPos + this->height / 2) {
              // our element's upper-left edge is in our lower-left quadrant.
              targNodeIndices->push(2);

              if (elHorzPos + elWidth > this->horzPos + this->width / 2) {
                // our elements's right edge is in another child node.
                targNodeIndices->push(0);
              }

            } else {
              // our element's uppler-left edge is in our lower-right quadrant.
              targNodeIndices->push(3);
            }

          }

          unsigned char numTargNodes = targNodeIndices->getLength();

          for (unsigned char targNodeIndicesIdx = 0; targNodeIndicesIdx < numTargNodes; targNodeIndicesIdx++) {
            unsigned char targNodeIdx = targNodeIndices->get(targNodeIndicesIdx);
            QuadNode* targNode = this->children->get(targNodeIdx);

            if (targNode == NULL) {
              uint32_t newNodeHorzPos = 0;
              uint32_t newNodeVertPos = 0;
              uint32_t newNodeWidth = this->width / 2;
              uint32_t newNodeHeight = this->height / 2;

              if (targNodeIdx == 0) {
                // upper-right corner
                newNodeHorzPos = this->horzPos + (this->width / 2);
                newNodeVertPos = this->vertPos;
              } else if (targNodeIdx == 1) {
                // upper-left corner
                newNodeHorzPos = this->horzPos;
                newNodeVertPos = this->vertPos;
              } else if (targNodeIdx == 2) {
                // lower-left corner
                newNodeHorzPos = this->horzPos;
                newNodeVertPos = this->vertPos + (this->height / 2);
              } else {
                // lower-right corner
                newNodeHorzPos = this->horzPos + (this->width / 2);
                newNodeVertPos = this->vertPos + (this->height / 2);
              }

              targNode = new QuadNode(newNodeHorzPos, newNodeVertPos, newNodeWidth, newNodeHeight);

              this->children->set(targNodeIdx, targNode);
            }

            targNode->insert(elHorzPos, elVertPos, elWidth, elHeight, elCallback);
          }

        //} else {
        //  // our element is not in this node so do nothing.
        //}

      }

      List<QuadNodeEntry*>* query(uint32_t regHorzPos, uint32_t regVertPos, uint32_t regWidth, uint32_t regHeight) {
        List<QuadNodeEntry*>* retList = new List<QuadNodeEntry*>();

        if (this->width < regWidth && this->height < regHeight) {
          // perform actions...
          unsigned char numChildren = this->children->getLength();

          for (unsigned char childIdx; childIdx < numChildren; childIdx++) {
            QuadNode* childNode = this->children->get(childIdx);
          }

        } else {
          // recurse!
          //List<QuadNode*>* targChildren = new List<QuadNode*>();

          unsigned char numChildren = this->children->getLength();

          for (unsigned char childIdx; childIdx < numChildren; childIdx++) {
            QuadNode* childNode = this->children->get(childIdx);

            if (
              (
                (childNode->horzPos > regHorzPos) &&
                (childNode->vertPos > regVertPos)
              ) || (
                (childNode->horzPos + childNode->width < regHorzPos + regWidth) &&
                (childNode->vertPos + childNode->height < regHorzPos + regWidth)
              )
            ) {
              //targChildren->push(childNode);
              uint32_t numElements = childNode->elements->getLength();

              for (unsigned char elIdx = 0; elIdx < numElements; elIdx++) {
                QuadNodeEntry* entry = childNode->elements->get(elIdx);

                //void*(*callback)(void*, void*, void*) = entry->callback;

                //callback(childNode, NULL, NULL);
                retList->push(entry);
              }

            }

          }

        }

        return retList;
      }

  };

#endif
