
#include "../../lib/scene/character.hpp"


class PlayerOne: public SceneCharacter {

  public:

    PlayerOne() {
      Sprite* standingStillSprite = new Sprite();
      Sprite* movingForwardSprite = new Sprite();
      Sprite* turningLeftSprite = new Sprite();
      Sprite* turningRightSprite = new Sprite();

      Image* shipStandingStill = Image::load("./ship_sheet.bmp", 390, 150, 75, 75);
      Image* shipTurningLeft = Image::load("./ship_sheet.bmp", 490, 50, 75, 75);
      Image* shipTurningRight = Image::load("./ship_sheet.bmp", 190, 50, 75, 75);
      Image* shipMovingForward = Image::load("./ship_sheet.bmp", 90, 50, 75, 75);

      standingStillSprite->addFrame(shipStandingStill, 0);
      movingForwardSprite->addFrame(shipMovingForward, 0);
      turningLeftSprite->addFrame(shipTurningLeft, 0);
      turningRightSprite->addFrame(shipTurningRight, 0);

      standingStillSprite->addFrame(1);
      movingForwardSprite->addFrame(1);
      turningLeftSprite->addFrame(1);
      turningRightSprite->addFrame(1);

      standingStillSprite->setLoop(false);
      movingForwardSprite->setLoop(false);
      turningLeftSprite->setLoop(false);
      turningRightSprite->setLoop(false);

      this->addSprite("standing_still", standingStillSprite);
      this->addSprite("moving_forward", movingForwardSprite);
      this->addSprite("turning_left", turningLeftSprite);
      this->addSprite("turning_right", turningRightSprite);

      this->setAction("standing_still");


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
