
#ifndef _GAME_PLAYER_HPP

  #define _GAME_PLAYER_HPP

  #include "../../lib/core/keyboard.hpp"
  #include "../../lib/core/image.hpp"
  #include "../../lib/runtime/sprite.hpp"
  #include "../../lib/runtime/data/trajectory.hpp"
  #include "../../lib/runtime/data/position.hpp"
  #include "../../lib/runtime/data/angle.hpp"
  #include "../../lib/runtime/data/scale.hpp"
  #include "../../lib/runtime/data/view.hpp"
  #include "../../lib/scene.hpp"
  #include "../../lib/scene/character.hpp"
  #include "./bullet.hpp"
  #include "./background.hpp"


  unsigned long int lastBulletTimestamp = 0;

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

      static Player* loadAssets(Scene* scene, void*(*callback)(void*, void*)) {
        Player* player = new Player();

        Sprite* standingStillSprite = new Sprite();
        Sprite* movingForwardSprite = new Sprite();
        Sprite* turningLeftSprite = new Sprite();
        Sprite* turningRightSprite = new Sprite();

        Image* shipStandingStill = Image::load("./ship_sheet.png", 390, 150, 75, 75);
        Image* shipTurningLeft = Image::load("./ship_sheet.png", 490, 50, 75, 75);
        Image* shipTurningRight = Image::load("./ship_sheet.png", 190, 50, 75, 75);
        Image* shipMovingForward = Image::load("./ship_sheet.png", 90, 50, 75, 75);

        standingStillSprite->addFrame(shipStandingStill, 0);
        movingForwardSprite->addFrame(shipMovingForward, 0);
        turningLeftSprite->addFrame(shipTurningLeft, 0);
        turningRightSprite->addFrame(shipTurningRight, 0);

        standingStillSprite->setLoop(false);
        movingForwardSprite->setLoop(false);
        turningLeftSprite->setLoop(false);
        turningRightSprite->setLoop(false);

        player->addSprite("standing_still", standingStillSprite);
        player->addSprite("moving_forward", movingForwardSprite);
        player->addSprite("turning_left", turningLeftSprite);
        player->addSprite("turning_right", turningRightSprite);

        player->setAction("standing_still");

        Scale* playerScale = (Scale*)player->state->get("scale");

        playerScale->horz = 1.0;
        playerScale->vert = 1.0;

        player->onEvaluate(callback, scene);

        return player;
      }

  };

#endif
