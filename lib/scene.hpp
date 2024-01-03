
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


      void evaluateCollision() {
        uint32_t numElements = elements->getLength();

        for (uint32_t baseElsIdx = 0; baseElsIdx < numElements - 1; baseElsIdx++) {
          SceneBase* baseEl = this->elements->get(baseElsIdx);

          for (uint32_t testElsIdx = baseElsIdx + 1; testElsIdx < numElements; testElsIdx++) {
            SceneBase* testEl = this->elements->get(testElsIdx);

            //if (baseElsIdx == testElsIdx) {
            //  continue;
            //}

            if (baseEl->isActive && testEl->isActive) {
              // TODO: We should differentiate between 'active' and 'visible'.
              Position* baseElPos = (Position*)baseEl->state->get("absolute_position");
              Position* testElPos = (Position*)testEl->state->get("absolute_position");

              Size* baseElSize = new Size(baseEl->width, baseEl->height);
              Size* testElSize = new Size(testEl->width, testEl->height);

              bool hasCollided = Collision::evaluate(baseElPos, baseElSize, testElPos, testElSize);

              if (hasCollided) {
                uint32_t baseElCharId = baseEl->getIdentifier();
                uint32_t testElCharId = testEl->getIdentifier();

                char* baseElHookId = new char[Hook::ID_LENGTH];
                // TODO: char baseElHookId[Hook::ID_LENGTH];
                char* testElHookId = new char[Hook::ID_LENGTH];
                // TODO: char testElHookId[Hook::ID_LENGTH];

                Hook::generateIdentifier(baseElHookId, "hook", baseElCharId, "onCollision", "action");
                Hook::executeCallback(baseElHookId, (void*)testEl);

                Hook::generateIdentifier(testElHookId, "hook", testElCharId, "onCollision", "action");
                Hook::executeCallback(testElHookId, (void*)baseEl);
              }

            }

          }

        }

      }


      void evaluate() {
        uint32_t elementsLen = this->elements->getLength();
        uint32_t backgroundsLen = this->backgrounds->getLength();
        uint32_t foregroundsLen = this->foregrounds->getLength();

        for (uint32_t elementsIdx = 0; elementsIdx < elementsLen; elementsIdx++) {
          SceneBase* element = this->elements->get(elementsIdx);


          if (element->isActive) {
            // TODO: We should differentiate between 'active' and 'visible'.
            element->evaluate();
          }

        }

        evaluateCollision();

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
