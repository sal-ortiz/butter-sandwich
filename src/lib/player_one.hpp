
#include "../../lib/scene/character.hpp"


class PlayerOne: public SceneCharacter {

  public:

    PlayerOne() {
      Trajectory* traj = (Trajectory*)this->state->get("trajectory");

      traj->positionRate.horz = 0.90;
      traj->positionRate.vert = 0.90;
      traj->positionRate.depth = 0.90;

      traj->angleRate.pitch = 0.90;
      traj->angleRate.roll = 0.90;
      traj->angleRate.yaw = 0.90;

      traj->scaleRate.horz = 0.90;
      traj->scaleRate.vert = 0.90;
      traj->scaleRate.depth = 0.90;
    }

};
