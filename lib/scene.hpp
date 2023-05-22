

#ifndef _SCENE_HPP

  #define _SCENE_HPP

  #include <string.h>

  #include "./runtime/data/size.hpp"
  #include "./runtime/data/view.hpp"
  #include "./scene/base.hpp"
  #include "./scene/character.hpp"
  #include "./scene/background.hpp"
  #include "./scene/element.hpp"


  class Scene: public SceneBase {

    private:

      List<SceneBase*>* elements;


    public:

      Size* size;
      View* view;

      Scene() {
        this->elements = new List<SceneBase*>();

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

      SceneBase* getElement(const char* name) {
        List<SceneBase*>* elements = this->elements;

        unsigned long int elementsLen = this->getNumElements();

        for (unsigned long int elementsIdx = 0; elementsIdx < elementsLen; elementsIdx++) {
          SceneBase* element = this->elements->get(elementsIdx);

          int cmpRes = strcmp(element->getName(), name);

          if (cmpRes == 0) {
            return element;
          }

        }

        return (SceneBase*)NULL;
      }

      void evaluate() {
        List<SceneBase*>* elements = this->elements;

        unsigned long int elementsLen = elements->getLength();

        for (unsigned long int elementsIdx = 0; elementsIdx < elementsLen; elementsIdx++) {
          SceneBase* element = this->elements->get(elementsIdx);

          if (element->isActive) {
            element->evaluate();
          }

        }

        SceneBase::evaluate();
      }

      void render(SDL_Renderer* renderer) {
        List<SceneBase*>* elements = this->elements;

        unsigned long int elementsLen = elements->getLength();

        for (unsigned long int elementsIdx = 0; elementsIdx < elementsLen; elementsIdx++) {
          SceneBase* element = this->elements->get(elementsIdx);

          if (element->isActive) {
            element->render(renderer);
          }

        }

      }

  };

#endif
