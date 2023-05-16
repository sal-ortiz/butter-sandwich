
#ifndef _GAME_BACKGROUND_HPP

  #define _GAME_BACKGROUND_HPP

  #include "../../lib/core/image.hpp"
  #include "../../lib/runtime/sprite.hpp"
  #include "../../lib/runtime/data/trajectory.hpp"
  #include "../../lib/runtime/data/view.hpp"
  #include "../../lib/scene/background.hpp"
  #include "../../lib/scene.hpp"
  #include "./player.hpp"
  #include "./bullet.hpp"


  class Background: public SceneBackground {

    public:

      Background() {
        Trajectory* traj = (Trajectory*)this->state->get("trajectory");

        traj->positionRate.horz = 0.90;
        traj->positionRate.vert = 0.90;
        traj->positionRate.depth = 0.90;

        this->isActive = true;
      }

      static Background* loadAssets(Scene* scene, void*(*callback)(void*, void*)) {
        Background* background = new Background();

        Sprite* backgroundSprite = new Sprite();
        Image* backgroundImage = Image::load("./background01.png", 0, 0, 3000, 1688);

        backgroundSprite->addFrame(backgroundImage, 0);
        backgroundSprite->setLoop(false);

        background->addSprite("background", backgroundSprite);
        background->setAction("background");

        background->onEvaluate(callback, scene);

        return background;
      }

  };

#endif
