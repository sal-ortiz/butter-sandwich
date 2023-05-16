
#ifndef _GAME_BULLET_HPP

  #define _GAME_BULLET_HPP

  #include "../../lib/core/image.hpp"
  #include "../../lib/runtime/sprite.hpp"
  #include "../../lib/runtime/data/position.hpp"
  #include "../../lib/runtime/data/angle.hpp"
  #include "../../lib/runtime/data/trajectory.hpp"
  #include "../../lib/runtime/data/view.hpp"
  #include "../../lib/scene/element.hpp"
  #include "./player.hpp"
  #include "./background.hpp"


  class Bullet: public SceneElement {

    public:

      static const unsigned long int DELAY = 200; // ms
      static const unsigned long int MAX_COUNT = 8;

      Bullet() {
        this->isActive = false;
        this->type = "bullet";
      }


      static Bullet* loadAssets(Scene* scene, void*(*callback)(void*, void*)) {
        Bullet* bullet = new Bullet();

        Sprite* bulletSprite = new Sprite();
        Image* bulletImage = Image::load("./bullet.png", 0, 0, 6, 6);

        bulletSprite->addFrame(bulletImage, 0);
        bulletSprite->setLoop(false);

        bullet->addSprite("bullet", bulletSprite);
        bullet->setAction("bullet");

        Position* absolutePos = new Position(-1, -1, -1);
        bullet->state->set("absolute_position", absolutePos);

        bullet->onEvaluate(callback, scene);

        return bullet;
      }

  };

#endif
