
#ifndef _GAME_BULLET_HPP

  #define _GAME_BULLET_HPP

  #include "../../lib/core/image.hpp"
  #include "../../lib/runtime/sprite.hpp"
  #include "../../lib/runtime/data/position.hpp"
  #include "../../lib/runtime/data/angle.hpp"
  #include "../../lib/runtime/data/trajectory.hpp"
  #include "../../lib/runtime/data/view.hpp"
  #include "../../lib/scene/element.hpp"
  #include "../../lib/scene.hpp"


  class Bullet: public SceneElement {

    public:

      static const uint32_t DELAY = 200; // ms
      static const uint32_t MAX_COUNT = 8;

      Bullet() {
        this->isActive = false;
        this->type = "bullet";
      }

      static Bullet* loadAssets(Scene* scene) {
        Bullet* bullet = new Bullet();

        Scale* scale = (Scale*)bullet->state->get("scale");
        Position* absPosition = (Position*)bullet->state->get("absolute_position");

        Sprite* sprite = new Sprite();
        Image* image = Image::load("./src/assets/bullet.png", 0, 0, 6, 6);

        sprite->addFrame(image, 0);
        sprite->setLoop(false);

        bullet->addSprite("bullet", sprite);
        bullet->setAction("bullet");

        scale->horz = 2.0;
        scale->vert = 2.0;

        absPosition->horz = -1;
        absPosition->vert = -1;

        bullet->onEvaluate(Bullet::evaluateCallback, scene);
        bullet->onCollision(Bullet::collisionCallback, scene);

        return bullet;
      }

      static void* collisionCallback(void* inp, void* dataOne, void* dataTwo) {
        SceneBase* targ = reinterpret_cast<SceneBase*>(inp);
        Scene* scene = reinterpret_cast<Scene*>(dataOne);


        printf("\n[%u] BULLET COLLISION!!", SDL_GetTicks());


        return NULL;
      }

      static void* evaluateCallback(void* inp, void* dataOne, void* dataTwo) {
        Bullet* bullet = reinterpret_cast<Bullet*>(inp);
        Scene* scene = reinterpret_cast<Scene*>(dataOne);

        Position* absPosition = (Position*)bullet->state->get("absolute_position");

        Position* position = (Position*)bullet->state->get("position");
        Trajectory* trajectory = (Trajectory*)bullet->state->get("trajectory");

        absPosition->horz += trajectory->position.horz;
        absPosition->vert += trajectory->position.vert;
        absPosition->depth += trajectory->position.depth;

        if (absPosition->horz > scene->view->position.horz
          && absPosition->horz < (scene->view->position.horz + scene->view->size.horz)
          && absPosition->vert > scene->view->position.vert
          && absPosition->vert < (scene->view->position.vert + scene->view->size.vert)
        ) {
          // our bullet is visible within our screen.
          position->horz = (absPosition->horz - scene->view->position.horz);
          position->vert = (absPosition->vert - scene->view->position.vert);

        }

        if (absPosition->horz < 0
          || absPosition->vert < 0
          || absPosition->horz > scene->size->horz
          || absPosition->vert > scene->size->vert
        ) {
          // our bullet has left our space.

          bullet->isActive = false;
        }

        return (void*)NULL;
      }

  };

#endif
