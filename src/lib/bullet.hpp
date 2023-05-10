
#include "../../lib/core/image.hpp"

#include "../../lib/runtime/sprite.hpp"

#include "../../lib/scene/element.hpp"


class Bullet: public SceneElement {

  public:

    bool isActive;


    Bullet() {
      this->isActive = false;
    }

};
