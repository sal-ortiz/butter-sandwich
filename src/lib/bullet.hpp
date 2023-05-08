
#include "../../lib/core/image.hpp"

#include "../../lib/runtime/sprite.hpp"

#include "../../lib/scene/element.hpp"


class Bullet: public SceneElement {

  public:

    Bullet() {
      Sprite* bulletSprite = new Sprite();
      Image* bulletImage = Image::load("./bullet.bmp", 0, 0, 6, 6);

      bulletSprite->addFrame(bulletImage, 0);
      bulletSprite->setLoop(false);

      this->addSprite("bullet", bulletSprite);
      this->setAction("bullet");
    }

};
