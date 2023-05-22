

#ifndef _SCENE_HPP

  #define _SCENE_HPP

  #include <string.h>

  #include "./scene/character.hpp"
  #include "./scene/background.hpp"
  #include "./scene/element.hpp"


  class Scene {

    private:

      List<SceneCharacter*>* characters;
      List<SceneBackground*>* backgrounds;
      List<SceneElement*>* elements;


    public:

      Size* size;
      View* view;

      Scene() {
        this->characters = new List<SceneCharacter*>();
        this->backgrounds = new List<SceneBackground*>();
        this->elements = new List<SceneElement*>();

        this->size = new Size();
        this->view = new View();
      }

      unsigned long int getNumCharacters() {
        return this->characters->getLength();
      }

      unsigned long int getNumBackgrounds() {
        return this->backgrounds->getLength();
      }

      unsigned long int getNumElements() {
        return this->elements->getLength();
      }

      void addCharacter(const char* name, SceneCharacter* character) {
        character->setName(name);

        this->characters->push(character);
      }

      SceneCharacter* getCharacter(const char* name) {
        List<SceneCharacter*>* characters = this->characters;

        unsigned long int charactersLen = characters->getLength();

        for (unsigned long int charactersIdx = 0; charactersIdx < charactersLen; charactersIdx++) {
          SceneCharacter* character = this->characters->get(charactersIdx);

          int cmpRes = strcmp(character->getName(), name);

          if (cmpRes == 0) {
            return character;
          }

        }

        return (SceneCharacter*)NULL;
      }

      void addBackground(const char* name, SceneBackground* background) {
        background->setName(name);

        this->backgrounds->push(background);
      }

      SceneBackground* getBackground(const char* name) {
        List<SceneBackground*>* background = this->backgrounds;

        unsigned long int backgroundsLen = backgrounds->getLength();

        for (unsigned long int backgroundsIdx = 0; backgroundsIdx < backgroundsLen; backgroundsIdx++) {
          SceneBackground* background = this->backgrounds->get(backgroundsIdx);

          int cmpRes = strcmp(background->getName(), name);

          if (cmpRes == 0) {
            return background;
          }

        }

        return (SceneBackground*)NULL;
      }

      void addElement(const char* name, SceneElement* element) {
        element->setName(name);

        this->elements->push(element);
      }

      SceneElement* getElement(const char* name) {
        List<SceneElement*>* elements = this->elements;

        unsigned long int elementsLen = this->getNumElements();

        for (unsigned long int elementsIdx = 0; elementsIdx < elementsLen; elementsIdx++) {
          SceneElement* element = this->elements->get(elementsIdx);

          int cmpRes = strcmp(element->getName(), name);

          if (cmpRes == 0) {
            return element;
          }

        }

        return (SceneElement*)NULL;
      }

      void evaluate() {
        List<SceneCharacter*>* characters = this->characters;
        List<SceneBackground*>* backgrounds = this->backgrounds;
        List<SceneElement*>* elements = this->elements;

        unsigned long int charactersLen = characters->getLength();
        unsigned long int backgroundsLen = backgrounds->getLength();
        unsigned long int elementsLen = elements->getLength();

        for (unsigned long int backgroundsIdx = 0; backgroundsIdx < backgroundsLen; backgroundsIdx++) {
          SceneBackground* background = this->backgrounds->get(backgroundsIdx);

          if (background->isActive) {
            background->evaluate();
          }

        }

        for (unsigned long int charactersIdx = 0; charactersIdx < charactersLen; charactersIdx++) {
          SceneCharacter* character = this->characters->get(charactersIdx);

          if (character->isActive) {
            character->evaluate();
          }

        }

        for (unsigned long int elementsIdx = 0; elementsIdx < elementsLen; elementsIdx++) {
          SceneElement* element = this->elements->get(elementsIdx);

          if (element->isActive) {
            element->evaluate();
          }

        }

      }

      void render(SDL_Renderer* renderer) {
        List<SceneCharacter*>* characters = this->characters;
        List<SceneBackground*>* backgrounds = this->backgrounds;
        List<SceneElement*>* elements = this->elements;

        unsigned long int charactersLen = characters->getLength();
        unsigned long int backgroundsLen = backgrounds->getLength();
        unsigned long int elementsLen = elements->getLength();

        for (unsigned long int backgroundsIdx = 0; backgroundsIdx < backgroundsLen; backgroundsIdx++) {
          SceneBackground* background = this->backgrounds->get(backgroundsIdx);

          if (background->isActive) {
            background->render(renderer);
          }

        }

        for (unsigned long int charactersIdx = 0; charactersIdx < charactersLen; charactersIdx++) {
          SceneCharacter* character = this->characters->get(charactersIdx);

          if (character->isActive) {
            character->render(renderer);
          }

        }

        for (unsigned long int elementsIdx = 0; elementsIdx < elementsLen; elementsIdx++) {
          SceneElement* element = this->elements->get(elementsIdx);

          if (element->isActive) {
            element->render(renderer);
          }

        }

      }

  };

#endif
