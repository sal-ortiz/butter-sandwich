
#ifndef _SCENE_HPP

  #define _SCENE_HPP

  #include <string.h>

  #include "./core/renderer.hpp"
  #include "./core/quadtree.hpp"
  #include "./runtime/collision.hpp"
  #include "./runtime/data/size.hpp"
  #include "./runtime/data/view.hpp"
  #include "./scene/base.hpp"
  #include "./scene/character.hpp"
  #include "./scene/background.hpp"
  #include "./scene/element.hpp"


  class Scene: public SceneBase {

    private:

      List<SceneBase*>* elements;
      List<SceneBase*>* backgrounds;
      List<SceneBase*>* foregrounds;

      Quadtree<SceneBase*>* quadtree;

    public:

      Size* size;
      View* view;

      Scene() {
        this->elements = new List<SceneBase*>();
        this->backgrounds = new List<SceneBase*>();
        this->foregrounds = new List<SceneBase*>();

        this->size = new Size();
        this->view = new View();
      }

      ~Scene() {
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

        this->quadtree = new Quadtree<SceneBase*>(sceneWidth, sceneHeight, 0, 0);

        uint32_t numEls = this->elements->getLength();

        for (uint32_t elIdx = 0; elIdx < numEls; elIdx++) {
          SceneBase* el = this->elements->get(elIdx);
          Position* elPos = (Position*)el->state->get("absolute_position");

          this->quadtree->insert(elPos->horz, elPos->vert, el->width, el->height, el);
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

          if (hitList->getLength() > 1) {

            for (uint32_t hitIdx = 0; hitIdx < hitList->getLength(); hitIdx++) {
              //QuadtreeElement<SceneBase*>*>* hitListEl = hitList->get(hitIdx);

              QuadtreeElement<SceneBase*>* hitEntry = hitList->get(hitIdx);
              SceneBase* hitEl = hitEntry->value;

              if (
                (/*el->isActive &&*/ hitEl->isActive)
                && (el->getIdentifier() != hitEl->getIdentifier())
              ) {
                uint32_t charId = el->getIdentifier();

                char* hookId = new char[Hook::ID_LENGTH];
                Hook::generateIdentifier(hookId, "hook", charId, "onCollision", "action");

                Hook::executeCallback(hookId, (void*)this);
              }

            }

          }

        }

      }

      void evaluate() {
        uint32_t elsLen = this->elements->getLength();
        uint32_t bgsLen = this->backgrounds->getLength();
        uint32_t fgsLen = this->foregrounds->getLength();


      for (uint32_t bgIdx = 0; bgIdx < bgsLen; bgIdx++) {
          SceneBase* bg = this->backgrounds->get(bgIdx);

          if (bg->isActive) {
            bg->evaluate();
          }

        }

        for (uint32_t elIdx = 0; elIdx < elsLen; elIdx++) {
          SceneBase* el = this->elements->get(elIdx);

          if (el->isActive) {
            el->evaluate();
          }

        }

        for (uint32_t fgIdx = 0; fgIdx < fgsLen; fgIdx++) {
          SceneBase* fg = this->foregrounds->get(fgIdx);

          if (fg->isActive) {
            fg->evaluate();
          }

        }

        this->populateCollision();
        this->evaluateCollision();

        SceneBase::evaluate();
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
