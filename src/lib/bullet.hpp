
#ifndef _GAME_BULLET_HPP

  #define _GAME_BULLET_HPP

  #include "../../lib/core/image.hpp"
  #include "../../lib/runtime/sprite.hpp"
  #include "../../lib/runtime/data/position.hpp"
  #include "../../lib/runtime/data/angle.hpp"
  #include "../../lib/runtime/data/trajectory.hpp"
  #include "../../lib/runtime/data/view.hpp"
  #include "../../lib/scene/element.hpp"


  class Bullet: public SceneElement {

    public:

      static const unsigned long int DELAY = 200; // ms
      static const unsigned long int MAX_COUNT = 8;

      Bullet() {
        this->isActive = false;
        this->type = "bullet";
      }

      static Bullet* loadAssets(Scene* scene) {
        Bullet* bullet = new Bullet();

        Scale* bulletScale = (Scale*)bullet->state->get("scale");

        Sprite* bulletSprite = new Sprite();
        Image* bulletImage = Image::load("./bullet.png", 0, 0, 6, 6);

        bulletSprite->addFrame(bulletImage, 0);
        bulletSprite->setLoop(false);

        bullet->addSprite("bullet", bulletSprite);
        bullet->setAction("bullet");

        bulletScale->horz = 2.0;
        bulletScale->vert = 2.0;

        Position* absolutePos = new Position(-1, -1, -1);
        bullet->state->set("absolute_position", absolutePos);

        bullet->onEvaluate(Bullet::evaluateCallback, scene);

        return bullet;
      }

      static void* evaluateCallback(void* inp, void* data) {
        Bullet* bullet = reinterpret_cast<Bullet*>(inp);
        Scene* scene = reinterpret_cast<Scene*>(data);

        Position* bulletAbsolutePos = (Position*)bullet->state->get("absolute_position");

        Position* bulletPos = (Position*)bullet->state->get("position");
        Trajectory* bulletTraj = (Trajectory*)bullet->state->get("trajectory");

        bulletAbsolutePos->horz += bulletTraj->position.horz;
        bulletAbsolutePos->vert += bulletTraj->position.vert;
        bulletAbsolutePos->depth += bulletTraj->position.depth;

        if (bulletAbsolutePos->horz > scene->view->position.horz
          && bulletAbsolutePos->horz < (scene->view->position.horz + scene->view->size.horz)
          && bulletAbsolutePos->vert > scene->view->position.vert
          && bulletAbsolutePos->vert < (scene->view->position.vert + scene->view->size.vert)
        ) {
          // our bullet is visible within our screen.
          bulletPos->horz = (bulletAbsolutePos->horz - scene->view->position.horz);
          bulletPos->vert = (bulletAbsolutePos->vert - scene->view->position.vert);

        }

        if (bulletAbsolutePos->horz < 0
          || bulletAbsolutePos->vert < 0
          || bulletAbsolutePos->horz > scene->size->horz
          || bulletAbsolutePos->vert > scene->size->vert
        ) {
          // our bullet has left our space.

          bullet->isActive = false;
        }

        return (void*)NULL;
      }

  };

#endif
