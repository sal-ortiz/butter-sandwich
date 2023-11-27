
#ifndef _SCENE_HPP

  #define _SCENE_HPP

  #include <string.h>

  #include "../lib/runtime/physics.hpp"
  #include "../lib/core/renderer.hpp"
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

      unsigned long int getNumElements() {
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
        unsigned long int elementsLen = this->elements->getLength();

        for (unsigned long int elementsIdx = 0; elementsIdx < elementsLen; elementsIdx++) {
          SceneBase* element = this->elements->get(elementsIdx);

          int cmpRes = strcmp(element->getName(), name);

          if (cmpRes == 0) {
            return element;
          }

        }

        return (SceneBase*)NULL;
      }

      SceneBase* getBackground(const char* name) {
        unsigned long int backgroundsLen = this->backgrounds->getLength();

        for (unsigned long int backgroundsIdx = 0; backgroundsIdx < backgroundsLen; backgroundsIdx++) {
          SceneBase* element = this->backgrounds->get(backgroundsIdx);

          int cmpRes = strcmp(element->getName(), name);

          if (cmpRes == 0) {
            return element;
          }

        }

        return (SceneBase*)NULL;
      }

      SceneBase* getForeground(const char* name) {
        unsigned long int foregroundsLen = this->foregrounds->getLength();

        for (unsigned long int foregroundsIdx = 0; foregroundsIdx < foregroundsLen; foregroundsIdx++) {
          SceneBase* element = this->foregrounds->get(foregroundsIdx);

          int cmpRes = strcmp(element->getName(), name);

          if (cmpRes == 0) {
            return element;
          }

        }

        return (SceneBase*)NULL;
      }

      void evaluate() {
        unsigned long int elementsLen = this->elements->getLength();
        unsigned long int backgroundsLen = this->backgrounds->getLength();
        unsigned long int foregroundsLen = this->foregrounds->getLength();

        // TODO: find a better way to get this value into Physics::Collision
        Collision::setWidth(this->size->horz);
        Collision::setHeight(this->size->vert);

        for (unsigned long int elementsIdx = 0; elementsIdx < elementsLen; elementsIdx++) {
          SceneBase* element = this->elements->get(elementsIdx);

          if (element->isActive) {
            element->evaluate();

            Collision::insert(element);
          }

        }

        for (unsigned long int backgroundsIdx = 0; backgroundsIdx < backgroundsLen; backgroundsIdx++) {
          SceneBase* element = this->backgrounds->get(backgroundsIdx);

          if (element->isActive) {
            element->evaluate();
          }

        }

        for (unsigned long int foregroundsIdx = 0; foregroundsIdx < foregroundsLen; foregroundsIdx++) {
          SceneBase* element = this->foregrounds->get(foregroundsIdx);

          if (element->isActive) {
            element->evaluate();
          }

        }

        Collision::evaluate();

        SceneBase::evaluate();
      }

      void render(Renderer* renderer) {
        unsigned long int elementsLen = this->elements->getLength();
        unsigned long int backgroundsLen = this->backgrounds->getLength();
        unsigned long int foregroundsLen = this->backgrounds->getLength();

        for (unsigned long int backgroundsIdx = 0; backgroundsIdx < backgroundsLen; backgroundsIdx++) {
          SceneBase* element = this->backgrounds->get(backgroundsIdx);

          if (element->isActive) {
            element->render(renderer);
          }

        }

        for (unsigned long int elementsIdx = 0; elementsIdx < elementsLen; elementsIdx++) {
          SceneBase* element = this->elements->get(elementsIdx);

          if (element->isActive) {
            element->render(renderer);
          }

        }

        for (unsigned long int foregroundsIdx = 0; foregroundsIdx < foregroundsLen; foregroundsIdx++) {
          SceneBase* element = this->foregrounds->get(foregroundsIdx);

          if (element->isActive) {
            element->render(renderer);
          }

        }

      }

  };

#endif
