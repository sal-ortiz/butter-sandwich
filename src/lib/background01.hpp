
#ifndef _GAME_BACKGROUND01_HPP

  #define _GAME_BACKGROUND01_HPP

  #include "../../lib/core/image.hpp"
  #include "../../lib/runtime/sprite.hpp"
  #include "../../lib/runtime/data/trajectory.hpp"
  #include "../../lib/runtime/data/view.hpp"
  #include "../../lib/scene/background.hpp"
  #include "../../lib/scene.hpp"


  class Background01: public SceneBackground {

    public:

      Background01() {
        Trajectory* trajectory = (Trajectory*)this->state->get("trajectory");

        trajectory->positionRate.horz = 0.90;
        trajectory->positionRate.vert = 0.90;
        trajectory->positionRate.depth = 0.90;

        this->isActive = true;
      }

      static Background01* loadAssets(Scene* scene) {
        Background01* background = new Background01();

        Sprite* sprite = new Sprite();
        Image* image = Image::load("./src/assets/background01.png", 0, 0, 3840, 2160);

        sprite->addFrame(image, 0);
        sprite->setLoop(false);

        background->addSprite("background", sprite);
        background->setAction("background");

        background->onEvaluate(Background01::evaluateCallback, scene);

        return background;
      }

      static void* evaluateCallback(void* inp, void* dataOne, void* dataTwo) {
        Background01* background = reinterpret_cast<Background01*>(inp);
        Scene* scene = reinterpret_cast<Scene*>(dataOne);

        Background00* baseBackground = (Background00*)scene->getElement("background00");;

        Trajectory* trajectory = (Trajectory*)background->state->get("trajectory");
        View* view = (View*)background->state->get("view");
        Position* absPosition = (Position*)background->state->get("absolute_position");
        Position* position = (Position*)background->state->get("position");

        // NOTE: This only needs to be set once.
        view->size.horz = scene->view->size.horz;
        view->size.vert = scene->view->size.vert;

        scene->view->position.horz += trajectory->position.horz;
        scene->view->position.vert += trajectory->position.vert;
        scene->view->position.depth += trajectory->position.depth;

        trajectory->position.horz *= trajectory->positionRate.horz;
        trajectory->position.vert *= trajectory->positionRate.vert;
        trajectory->position.depth *= trajectory->positionRate.depth;

        view->position.horz = scene->view->position.horz;
        view->position.vert = scene->view->position.vert;

        if (absPosition->horz >= 0) {

          if (view->position.horz < absPosition->horz) {
            // moving horizontally along our lefthand border
            position->horz = absPosition->horz - view->position.horz;

            view->position.horz = 0;

          } else {
            // moving horizontally along our righthand border and the center of the map
            view->position.horz = (view->position.horz - absPosition->horz) * ((float)background->width / (float)baseBackground->width);
          }

        } else {

          if (view->position.horz > background->width - (view->size.horz + abs(absPosition->horz))) {
            // moving horizontally along our righthand border
            position->horz = 0;

            view->size.horz = absPosition->horz + (background->width - view->position.horz);
          }

          view->position.horz = (view->position.horz - absPosition->horz) * ((float)background->width / (float)baseBackground->width);
        }

        if (absPosition->vert >= 0) {

          if (view->position.vert < absPosition->vert) {
            // moving vertically along our upper border
            position->vert = absPosition->vert - view->position.vert;

            view->position.vert = 0;

          } else {
            // moving vertically along our lower border and the center of the map
            view->position.vert = (view->position.vert - absPosition->vert) * ((float)background->height / (float)baseBackground->height);
          }

        } else {

          if (view->position.vert > background->height - (view->size.vert + abs(absPosition->vert))) {
            // moving around verticaly along our righthand border
            position->vert = 0;

            view->size.vert = absPosition->vert + (background->height - view->position.vert);

          }

          view->position.vert = (view->position.vert - absPosition->vert) * ((float)background->height / (float)baseBackground->height);
        }

        return (void*)NULL;
      }

  };

#endif
