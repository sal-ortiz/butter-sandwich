
#ifndef _GAME_BACKGROUND01_HPP

  #define _GAME_BACKGROUND01_HPP

  #include <core/image.hpp>
  #include <runtime/sprite.hpp>
  #include <runtime/data/trajectory.hpp>
  #include <runtime/data/view.hpp>
  #include <runtime/data/color.hpp>
  #include <scene/background.hpp>
  #include <scene.hpp>


  class Foreground00: public SceneBackground {

    public:

      Foreground00() {
        Trajectory* trajectory = (Trajectory*)this->state->get("trajectory");
        Color* color = (Color*)this->state->get("color");

        trajectory->positionRate.horz = 0.90;
        trajectory->positionRate.vert = 0.90;
        trajectory->positionRate.depth = 0.90;

        color->alpha = 180;

        this->isActive = true;
      }

      static Foreground00* loadAssets(Scene* scene) {
        Foreground00* foreground = new Foreground00();
        Sprite* sprite = new Sprite();
        Image* image = Image::load("./src/assets/background01.png", 0, 0, 3840, 2160);


        sprite->addFrame(image, 0);
        sprite->setLoop(false);

        foreground->addSprite("foreground", sprite);
        foreground->setAction("foreground");

        foreground->onEvaluate(Foreground00::evaluateCallback);

        return foreground;
      }

      static void* evaluateCallback(LinkedList<void*>* inp) {
        Foreground00* foreground = reinterpret_cast<Foreground00*>(inp->get(0));
        Scene* scene = reinterpret_cast<Scene*>(inp->get(1));

        Background00* baseBackground = (Background00*)scene->getBackground("background00");;

        Trajectory* trajectory = (Trajectory*)foreground->state->get("trajectory");
        View* view = (View*)foreground->state->get("view");
        Position* absPosition = (Position*)foreground->state->get("absolute_position");
        Position* position = (Position*)foreground->state->get("position");

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
            view->position.horz = (view->position.horz - absPosition->horz) * ((float)foreground->width / (float)baseBackground->width);
          }

        } else {

          if (view->position.horz > foreground->width - (view->size.horz + abs(absPosition->horz))) {
            // moving horizontally along our righthand border
            position->horz = 0;

            view->size.horz = absPosition->horz + (foreground->width - view->position.horz);
          }

          view->position.horz = (view->position.horz - absPosition->horz) * ((float)foreground->width / (float)baseBackground->width);
        }

        if (absPosition->vert >= 0) {

          if (view->position.vert < absPosition->vert) {
            // moving vertically along our upper border
            position->vert = absPosition->vert - view->position.vert;

            view->position.vert = 0;

          } else {
            // moving vertically along our lower border and the center of the map
            view->position.vert = (view->position.vert - absPosition->vert) * ((float)foreground->height / (float)baseBackground->height);
          }

        } else {

          if (view->position.vert > foreground->height - (view->size.vert + abs(absPosition->vert))) {
            // moving around verticaly along our righthand border
            position->vert = 0;

            view->size.vert = absPosition->vert + (foreground->height - view->position.vert);

          }

          view->position.vert = (view->position.vert - absPosition->vert) * ((float)foreground->height / (float)baseBackground->height);
        }

        return (void*)NULL;
      }

  };

#endif
