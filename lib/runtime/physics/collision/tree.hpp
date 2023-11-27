
#ifndef _COLLISION_TREE_HPP

  #define _COLLISION_TREE_HPP

  #include "../../../core/list.hpp"
  #include "../../../runtime/data/size.hpp"
  #include "../../../runtime/base.hpp"
  #include "../../../scene/base.hpp"
  #include "../../data/size.hpp"
  #include "../../data/position.hpp"

  #define MAX_QUADTREE_LEVELS 48


  class QuadNode {

    public:

      Size* size;

      List<SceneBase*>* elements;
      List<QuadNode*>* nodes;

      QuadNode(uint32_t width, uint32_t height) {
        this->size = new Size(width, height);

        this->elements = new List<SceneBase*>();
        this->nodes = new List<QuadNode*>();

        this->nodes->set(0, NULL);
        this->nodes->set(1, NULL);
        this->nodes->set(2, NULL);
        this->nodes->set(3, NULL);
      }

      ~QuadNode() {
        uint32_t numNodes = this->nodes->getLength();

        for (uint32_t nodesIdx = 0; nodesIdx < numNodes; nodesIdx++) {
          QuadNode* node = this->nodes->get(nodesIdx);

          if (node != NULL) {
            delete node;
          }

        }

      }

      void insert(SceneBase* el, uint32_t levelNum=0) {

        if (levelNum > MAX_QUADTREE_LEVELS) {
          return;
        }

        this->elements->unshift(el);

        Position* elPos = (Position*)el->state->get("position");

        float horzPos = elPos->horz;
        float vertPos = elPos->vert;

        uint8_t quadrant;

        if (horzPos > this->size->horz / 2) {

          if (vertPos < this->size->vert / 2) {
            quadrant = 1; // upper right
          } else {
            quadrant = 4; // lower right
          }

        } else {

          if (vertPos < this->size->vert / 2) {

            quadrant = 2; // upper left
          } else {
            quadrant = 3; // lower left
          }

        }

        QuadNode* childNode = this->nodes->get(quadrant - 1);

        if (childNode == NULL) {

          childNode = new QuadNode(
            this->size->horz / 2,
            this->size->vert / 2
          );

        }

        float nodeElHorzPos = horzPos;
        float nodeElVertPos = vertPos;

        if (quadrant == 1) {
          nodeElHorzPos = horzPos - (this->size->horz / 2);
        } else if (quadrant == 3) {
          nodeElVertPos = vertPos - (this->size->vert / 2);

        } else if (quadrant == 4) {
          nodeElHorzPos = horzPos - (this->size->horz / 2);
          nodeElVertPos = vertPos - (this->size->vert / 2);
        }

        childNode->insert(el, (levelNum + 1));

        this->nodes->set(quadrant - 1, childNode);
      }

      void evaluate() {
        uint32_t numNodes = this->nodes->getLength();

        for (uint32_t nodeIdx = 0; nodeIdx < numNodes; nodeIdx++) {
          QuadNode* node = this->nodes->get(nodeIdx);

          if (node == NULL) {
            continue;
          }

          if (this->elements->getLength() > 1 &&
            node->elements->getLength() <= 1
          ) {

            uint32_t numEls = this->elements->getLength();

            for (uint32_t elsIdx = 0; elsIdx < numEls; elsIdx++) {
              SceneBase* el = this->elements->get(elsIdx);

              if (
                el->width > node->size->horz &&
                el->height > node->size->vert
              ) {
                uint32_t charId = el->getIdentifier();

                char* hookId = new char[Hook::ID_LENGTH];
                // TODO: char hookId[Hook::ID_LENGTH];
                Hook::generateIdentifier(hookId, "hook", charId, "onCollision", "action");

                el->executeCallback(hookId, (void*)this, this->elements);
              }

            }

          } else {
            node->evaluate();
          }

        }

      }

  };

#endif
