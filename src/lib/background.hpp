
#include "../../lib/scene/background.hpp"


class Background: public SceneBackground {

  public:

    Background() {
      Sprite* backgroundSprite = new Sprite();
      Image* backgroundImage = Image::load("./background.bmp", 0, 0, 3000, 1688);

      backgroundSprite->addFrame(backgroundImage, 0);
      backgroundSprite->setLoop(false);

      this->addSprite("background", backgroundSprite);
      this->setAction("background");


      Trajectory* traj = (Trajectory*)this->state->get("trajectory");

      traj->positionRate.horz = 0.90;
      traj->positionRate.vert = 0.90;
      traj->positionRate.depth = 0.90;
    }

};


