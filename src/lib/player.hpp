
#include "../../lib/core/image.hpp"

#include "../../lib/runtime/sprite.hpp"

#include "../../lib/scene/character.hpp"


class Player: public SceneCharacter {

  public:

    Player() {
      Trajectory* traj = (Trajectory*)this->state->get("trajectory");

      traj->positionRate.horz = 0.925;
      traj->positionRate.vert = 0.925;
      traj->positionRate.depth = 0.925;

      traj->angleRate.pitch = 0.85;
      traj->angleRate.roll = 0.85;
      traj->angleRate.yaw = 0.85;

      traj->scaleRate.horz = 0.90;
      traj->scaleRate.vert = 0.90;
      traj->scaleRate.depth = 0.90;

      this->isActive = true;
    }

};
