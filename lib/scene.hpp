
#ifndef _SCENE_HPP

  #define _SCENE_HPP

  #include <string.h>

  #include "./core/renderer.hpp"
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
        uint32_t elListLen = this->elements->getLength();
        uint32_t bgListLen = this->backgrounds->getLength();
        uint32_t fgListLen = this->foregrounds->getLength();

        for (uint32_t elIdx = 0; elIdx < elListLen; elIdx++) {
          SceneBase* element = this->elements->get(elIdx);

          delete element;
        }

        for (uint32_t fgIdx = 0; fgIdx < fgListLen; fgIdx++) {
          SceneBase* element = this->foregrounds->get(fgIdx);

          delete element;
        }

        for (uint32_t bgIdx = 0; bgIdx < bgListLen; bgIdx++) {
          SceneBase* element = this->backgrounds->get(bgIdx);

          delete element;
        }

        delete this->elements;
        delete this->foregrounds;
        delete this->backgrounds;
      }

      uint32_t getNumElements() {
        return this->elements->getLength();
      }

      void addElement(const char* name, SceneBase* element) {
        element->setName(name);

        this->elements->push(element);
      }

      void addBackground(const char* name, SceneBase* element) {
        element->setName(name);

        this->backgrounds->push(element);
      }

      void addForeground(const char* name, SceneBase* element) {
        element->setName(name);

        this->foregrounds->push(element);
      }

      SceneBase* getElement(const char* name) {
        uint32_t elementsLen = this->elements->getLength();

        for (uint32_t elementsIdx = 0; elementsIdx < elementsLen; elementsIdx++) {
          SceneBase* element = this->elements->get(elementsIdx);

          int32_t cmpRes = strcmp(element->getName(), name);

          if (cmpRes == 0) {
            return element;
          }

        }

        return (SceneBase*)NULL;
      }

      SceneBase* getBackground(const char* name) {
        uint32_t backgroundsLen = this->backgrounds->getLength();

        for (uint32_t backgroundsIdx = 0; backgroundsIdx < backgroundsLen; backgroundsIdx++) {
          SceneBase* element = this->backgrounds->get(backgroundsIdx);

          int32_t cmpRes = strcmp(element->getName(), name);

          if (cmpRes == 0) {
            return element;
          }

        }

        return (SceneBase*)NULL;
      }

      SceneBase* getForeground(const char* name) {
        uint32_t foregroundsLen = this->foregrounds->getLength();

        for (uint32_t foregroundsIdx = 0; foregroundsIdx < foregroundsLen; foregroundsIdx++) {
          SceneBase* element = this->foregrounds->get(foregroundsIdx);

          int32_t cmpRes = strcmp(element->getName(), name);

          if (cmpRes == 0) {
            return element;
          }

        }

        return (SceneBase*)NULL;
      }

      void evaluate() {
        uint32_t elementsLen = this->elements->getLength();
        uint32_t backgroundsLen = this->backgrounds->getLength();
        uint32_t foregroundsLen = this->foregrounds->getLength();

        for (uint32_t elementsIdx = 0; elementsIdx < elementsLen; elementsIdx++) {
          SceneBase* element = this->elements->get(elementsIdx);


          if (element->isActive) {
            element->evaluate();

            Position* elPos = (Position*)element->state->get("absolute_position");
            Size* elSize = new Size(element->width, element->height);

            Collision::insert(elPos->horz, elPos->vert, elSize->horz, elSize->vert, NULL);
          }

        }

        Collision::evaluate();


        for (uint32_t backgroundsIdx = 0; backgroundsIdx < backgroundsLen; backgroundsIdx++) {
          SceneBase* element = this->backgrounds->get(backgroundsIdx);

          if (element->isActive) {
            element->evaluate();

          }

        }

        for (uint32_t foregroundsIdx = 0; foregroundsIdx < foregroundsLen; foregroundsIdx++) {
          SceneBase* element = this->foregrounds->get(foregroundsIdx);

          if (element->isActive) {
            element->evaluate();

          }

        }

        Collision::clear();

        SceneBase::evaluate();
      }

      void render(Renderer* renderer) {
        uint32_t elementsLen = this->elements->getLength();
        uint32_t backgroundsLen = this->backgrounds->getLength();
        uint32_t foregroundsLen = this->backgrounds->getLength();

        for (uint32_t backgroundsIdx = 0; backgroundsIdx < backgroundsLen; backgroundsIdx++) {
          SceneBase* element = this->backgrounds->get(backgroundsIdx);

          if (element->isActive) {
            element->render(renderer);
          }

        }

        for (uint32_t elementsIdx = 0; elementsIdx < elementsLen; elementsIdx++) {
          SceneBase* element = this->elements->get(elementsIdx);

          if (element->isActive) {
            element->render(renderer);
          }

        }

        for (uint32_t foregroundsIdx = 0; foregroundsIdx < foregroundsLen; foregroundsIdx++) {
          SceneBase* element = this->foregrounds->get(foregroundsIdx);

          if (element->isActive) {
            element->render(renderer);
          }

        }

      }

  };

#endif
