
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

      static Background* loadAssets(Scene* scene) {
        Background* background = new Background();

        Sprite* backgroundSprite = new Sprite();
        Image* backgroundImage = Image::load("./background01.png", 0, 0, 3000, 1688);

        backgroundSprite->addFrame(backgroundImage, 0);
        backgroundSprite->setLoop(false);

        background->addSprite("background", backgroundSprite);
        background->setAction("background");

        background->onEvaluate(Background::evaluateCallback, scene);

        return background;
      }

      static void* evaluateCallback(void* inp, void* data) {
        Background* background = reinterpret_cast<Background*>(inp);
        Scene* scene = reinterpret_cast<Scene*>(data);

        Trajectory* backgroundTraj = (Trajectory*)background->state->get("trajectory");

        scene->view->position.horz += backgroundTraj->position.horz;
        scene->view->position.vert += backgroundTraj->position.vert;
        scene->view->position.depth += backgroundTraj->position.depth;

        backgroundTraj->position.horz *= backgroundTraj->positionRate.horz;
        backgroundTraj->position.vert *= backgroundTraj->positionRate.vert;
        backgroundTraj->position.depth *= backgroundTraj->positionRate.depth;

        return (void*)NULL;
      }

  };

#endif
