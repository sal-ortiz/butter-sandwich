

#include "../../lib/scene/character.hpp"


class PlayerOne: public SceneCharacter {

  public:

    PlayerOne() {
      this->trajectory->positionRate.horz = 0.90;
      this->trajectory->positionRate.vert = 0.90;
      this->trajectory->positionRate.depth = 0.90;

      this->trajectory->angleRate.pitch = 0.90;
      this->trajectory->angleRate.roll = 0.90;
      this->trajectory->angleRate.yaw = 0.90;

      this->trajectory->scaleRate.horz = 0.90;
      this->trajectory->scaleRate.vert = 0.90;
      this->trajectory->scaleRate.depth = 0.90;
    }







};
