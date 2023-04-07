
#include "../../lib/scene/background.hpp"


class Background: public SceneBackground {

  public:

    Background() {
      Trajectory* traj = (Trajectory*)this->state->get("trajectory");

      traj->positionRate.horz = 0.90;
      traj->positionRate.vert = 0.90;
      traj->positionRate.depth = 0.90;
    }

};


