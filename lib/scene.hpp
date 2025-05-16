
#ifndef _SCENE_HPP

  #define _SCENE_HPP

  #include <string.h>

  #include <core/renderer.hpp>
  #include <core/quadtree.hpp>
  #include <core/list/linked_list.hpp>
  #include <runtime/collision.hpp>
  #include <runtime/data/size.hpp>
  #include <runtime/data/view.hpp>
  #include <scene/base.hpp>
  #include <scene/character.hpp>
  #include <scene/background.hpp>
  #include <scene/element.hpp>

  #define COLLISION_EVAL_FRAME_INTERVAL   3


  class Scene: public SceneBase {

    private:

      LinkedList<SceneBase*>* elements;
      LinkedList<SceneBase*>* backgrounds;
      LinkedList<SceneBase*>* foregrounds;

      Quadtree<SceneBase*>* quadtree;

      uint8_t collisionFrameCount;


    public:

      Size* size;
      View* view;

      Scene() {
        this->elements = new LinkedList<SceneBase*>();
        this->backgrounds = new LinkedList<SceneBase*>();
        this->foregrounds = new LinkedList<SceneBase*>();

        this->size = new Size();
        this->view = new View();

        this->quadtree = NULL;

        this->collisionFrameCount = 0;
      }

      ~Scene() {
        // TODO: It might make more sense to have the
        //       code that created these elements delete
        //       them instead of doing it here.
        uint32_t elsLen = this->elements->getLength();
        uint32_t bgsLen = this->backgrounds->getLength();
        uint32_t fgsLen = this->foregrounds->getLength();

        for (uint32_t elIdx = 0; elIdx < elsLen; elIdx++) {
          SceneBase* el = this->elements->get(elIdx);

          delete el;
        }

        for (uint32_t fgIdx = 0; fgIdx < fgsLen; fgIdx++) {
          SceneBase* fg = this->foregrounds->get(fgIdx);

          delete fg;
        }

        for (uint32_t bgIdx = 0; bgIdx < bgsLen; bgIdx++) {
          SceneBase* bg = this->backgrounds->get(bgIdx);

          delete bg;
        }

        delete this->elements;
        delete this->foregrounds;
        delete this->backgrounds;

        delete this->size;
        delete this->view;
      }

      uint32_t getNumElements() {
        return this->elements->getLength();
      }

      void addElement(const char* name, SceneBase* el) {
        el->setName(name);

        this->elements->push(el);
      }

      void addBackground(const char* name, SceneBase* el) {
        el->setName(name);

        this->backgrounds->push(el);
      }

      void addForeground(const char* name, SceneBase* el) {
        el->setName(name);

        this->foregrounds->push(el);
      }

      SceneBase* getElement(const char* name) {
        uint32_t elsLen = this->elements->getLength();

        for (uint32_t elIdx = 0; elIdx < elsLen; elIdx++) {
          SceneBase* element = this->elements->get(elIdx);

          int32_t cmp = strcmp(element->getName(), name);

          if (cmp == 0) {
            return element;
          }

        }

        return (SceneBase*)NULL;
      }

      SceneBase* getBackground(const char* name) {
        uint32_t len = this->backgrounds->getLength();

        for (uint32_t idx = 0; idx < len; idx++) {
          SceneBase* el = this->backgrounds->get(idx);

          int32_t cmp = strcmp(el->getName(), name);

          if (cmp == 0) {
            return el;
          }

        }

        return (SceneBase*)NULL;
      }

      SceneBase* getForeground(const char* name) {
        uint32_t len = this->foregrounds->getLength();

        for (uint32_t idx = 0; idx < len; idx++) {
          SceneBase* el = this->foregrounds->get(idx);

          int32_t cmp = strcmp(el->getName(), name);

          if (cmp == 0) {
            return el;
          }

        }

        return (SceneBase*)NULL;
      }

      void populateCollision() {
        uint32_t sceneWidth = this->size->horz;
        uint32_t sceneHeight = this->size->vert;

        // TODO: delete  old this->quadtree entries.

        this->quadtree = new Quadtree<SceneBase*>(sceneWidth, sceneHeight);

        uint32_t numEls = this->elements->getLength();

        for (uint32_t elIdx = 0; elIdx < numEls; elIdx++) {
          SceneBase* el = this->elements->get(elIdx);

          if (el->isActive == true) {
            Position* elPos = (Position*)el->state->get("absolute_position");

            this->quadtree->insert(elPos->horz, elPos->vert, el->width, el->height, el);

          }

        }

      }

      void evaluateCollision() {
        uint32_t numEls = elements->getLength();

        for (uint32_t baseElsIdx = 0; baseElsIdx < numEls - 1; baseElsIdx++) {
          SceneBase* el = this->elements->get(baseElsIdx);
          Position* pos = (Position*)el->state->get("absolute_position");

          if (!el->isActive) {
            continue;
          }

          LinkedList<QuadtreeElement<SceneBase*>*>* hitList = this->quadtree->query(pos->horz, pos->vert, el->width, el->height);

          if (hitList && hitList->getLength() > 1) {

            for (uint32_t hitIdx = 0; hitIdx < hitList->getLength(); hitIdx++) {
              QuadtreeElement<SceneBase*>* hitEntry = hitList->get(hitIdx);
              SceneBase* hitEl = hitEntry->value;

              if (!hitEl->isActive) {
                continue;
              }

              if (el->getIdentifier() != hitEl->getIdentifier()) {
                Position* elPos = (Position*)el->state->get("absolute_position");
                Position* hitElPos = (Position*)hitEl->state->get("absolute_position");

                //Size* elSize = (Size*)el->state->get("size");
                //Size* hitElSize = (Size*)hitEl->state->get("size");

                uint32_t elLeft = elPos->horz;
                //uint32_t elRight = elPos->horz + elSize->horz;
                uint32_t elRight = elPos->horz + el->width;
                uint32_t elTop = elPos->vert;
                //uint32_t elBottom = elPos->vert + elSize->vert;
                uint32_t elBottom = elPos->vert + el->height;

                uint32_t hitElLeft = hitElPos->horz;
                //uint32_t hitElRight = hitElPos->horz + hitElSize->horz;
                uint32_t hitElRight = hitElPos->horz + hitEl->width;
                uint32_t hitElTop = hitElPos->vert;
                //uint32_t hitElBottom = hitElPos->vert + hitElSize->vert;
                uint32_t hitElBottom = hitElPos->vert + hitEl->height;

                if (
                  (
                    // bottom-right of A and upper-left of B
                    elLeft < hitElLeft && elRight > hitElLeft &&
                    elTop < hitElTop && elBottom > hitElTop
                  ) || (
                    // upper-right of A and bottom left of B
                    elLeft < hitElLeft && elRight > hitElLeft &&
                    elTop < hitElBottom && elBottom > hitElBottom

                  ) || (
                    // right of A within left of B
                    elLeft < hitElLeft && elRight > hitElLeft &&
                    elTop > hitElTop && elBottom < hitElBottom
                  ) || (
                    // right of A around left of B
                    elLeft < hitElLeft && elRight > hitElLeft &&
                    elTop < hitElTop && elBottom > hitElBottom

                  ) || (
                    // top of A arround and bottom of B
                    elLeft < hitElLeft && elRight > hitElRight &&
                    elTop < hitElTop && elBottom > hitElTop
                  ) || (
                    // bottom of A around top of B
                    elLeft < hitElLeft && elRight > hitElRight &&
                    elBottom > hitElTop && elBottom < hitElBottom

                  ) || (

                    // bottom-right of B and top-left of A
                    hitElLeft < elLeft && hitElRight > elLeft &&
                    hitElTop < elTop && hitElBottom > elTop
                  ) || (
                    // top-right of B and bottom-left of A
                    hitElLeft < elLeft && hitElRight > elLeft &&
                    hitElTop < elBottom && hitElBottom > elBottom

                  ) || (
                    // right of B within left of A
                    hitElLeft < elLeft && hitElRight > elLeft &&
                    hitElTop > elTop && hitElBottom < elBottom
                  ) || (
                    // right of B around left of A
                    hitElLeft < elLeft && hitElRight > elLeft &&
                    hitElTop < elTop && hitElBottom > elBottom

                  ) || (
                    // bottom of A within top of B
                    hitElLeft < elLeft && hitElRight > elRight &&
                    hitElTop < elTop && hitElBottom > elTop
                  ) || (
                    // top of B around top of A
                    hitElLeft < elLeft && hitElRight > elRight &&
                    hitElBottom > elTop && hitElBottom < elBottom

                  ) || (

                    // B wihin A
                    elLeft < hitElLeft && elRight > hitElRight &&
                    elTop < hitElTop && elBottom > hitElBottom
                  ) || (
                    // A within B
                    hitElLeft < elLeft && hitElRight > elRight &&
                    hitElTop < elTop && hitElBottom > elBottom
                  )

                ) {
                  uint32_t charId = el->getIdentifier();

                  char* hookId = new char[Hook::ID_LENGTH];
                  Hook::generateIdentifier(hookId, "hook", charId, "onCollision", "action");

                  Hook::executeCallback(hookId, (void*)this);

                  delete hookId;
                }

              }

            }

          }

          if (hitList != NULL) {
            delete hitList;
          }

        }

        delete this->quadtree;
        this->quadtree = NULL;
      }

      void evaluate() {
        uint32_t elsLen = this->elements->getLength();
        uint32_t bgsLen = this->backgrounds->getLength();
        uint32_t fgsLen = this->foregrounds->getLength();

        for (uint32_t bgIdx = 0; bgIdx < bgsLen; bgIdx++) {
          SceneBase* bg = this->backgrounds->get(bgIdx);

          if (bg->isActive) {
            bg->evaluate(this);
          }

        }

        for (uint32_t elIdx = 0; elIdx < elsLen; elIdx++) {
          SceneBase* el = this->elements->get(elIdx);

          if (el->isActive) {
            el->evaluate(this);
          }

        }

        for (uint32_t fgIdx = 0; fgIdx < fgsLen; fgIdx++) {
          SceneBase* fg = this->foregrounds->get(fgIdx);

          if (fg->isActive) {
            fg->evaluate(this);
          }

        }

        uint8_t collFrameInterval = COLLISION_EVAL_FRAME_INTERVAL;
        uint8_t collFrameCount = this->collisionFrameCount++;

        if ((collFrameCount % collFrameInterval) == 0) {
          this->populateCollision();
          this->evaluateCollision();
        }

        SceneBase::evaluate(this);
      }

      void render(Renderer* renderer) {
        uint32_t elsLen = this->elements->getLength();
        uint32_t bgsLen = this->backgrounds->getLength();
        uint32_t foregroundsLen = this->backgrounds->getLength();

        for (uint32_t bgIdx = 0; bgIdx < bgsLen; bgIdx++) {
          SceneBase* element = this->backgrounds->get(bgIdx);

          if (element->isActive) {
            element->render(renderer);
          }

        }

        for (uint32_t elIdx = 0; elIdx < elsLen; elIdx++) {
          SceneBase* element = this->elements->get(elIdx);

          if (element->isActive) {
            element->render(renderer);
          }

        }

        for (uint32_t fgIdx = 0; fgIdx < foregroundsLen; fgIdx++) {
          SceneBase* element = this->foregrounds->get(fgIdx);

          if (element->isActive) {
            element->render(renderer);
          }

        }

      }

  };

#endif
