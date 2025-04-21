
#ifndef _GAME_BULLET_HPP

  #define _GAME_BULLET_HPP

  #include <core/image.hpp>
  #include <runtime/sprite.hpp>
  #include <runtime/data/position.hpp>
  #include <runtime/data/angle.hpp>
  #include <runtime/data/trajectory.hpp>
  #include <runtime/data/view.hpp>
  #include <scene/element.hpp>
  #include <scene.hpp>


  class Bullet: public SceneElement {

    public:

      static const uint32_t DELAY = 200; // ms
      static const uint32_t MAX_COUNT = 8;

      Bullet() {
        this->isActive = false;
        this->type = "bullet";

        Trajectory* trajectory = (Trajectory*)this->state->get("trajectory");

        trajectory->colorRate.red = 45.0;
        trajectory->colorRate.green = 45.0;
        trajectory->colorRate.blue = 45.0;
        trajectory->colorRate.alpha = 45.0;


        //printf("(%s) identifier: %d\t/\tidentifierString: %s\n", this->type, this->getIdentifier(), this->getIdentifierString());
      }

      static Bullet* loadAssets(Scene* scene) {
        Bullet* bullet = new Bullet();

        Scale* scale = (Scale*)bullet->state->get("scale");
        Position* absPosition = (Position*)bullet->state->get("absolute_position");

        Sprite* sprite = new Sprite();
        Image* image = Image::load("./src/assets/bullet.png", 0, 0, 6, 6);

        sprite->addFrame(image, 0);
        sprite->setLoop(false);

        bullet->addSprite("bullet", sprite);
        bullet->setAction("bullet");

        scale->horz = 2.0;
        scale->vert = 2.0;

        absPosition->horz = -1;
        absPosition->vert = -1;

        bullet->onEvaluate(Bullet::evaluateCallback);
        bullet->onCollision(Bullet::collisionCallback);

        return bullet;
      }

      static void* collisionCallback(SceneBase* targ, Bullet* bullet, Scene* scene) {

        //printf("\n[%u] BULLET COLLISION!!", SDL_GetTicks());
//        printf("\n%d\n", targ->getIdentifier());
//        printf("\n%s\n", targ->type);

        //printf("\ntarg: (%s) %u\n", targ->type, targ->getIdentifier());
        //printf("\nbullet: (%s) %u\n\n", bullet->type, bullet->getIdentifier());

        return NULL;
      }

      static void* evaluateCallback(Bullet* bullet, Scene* scene) {
        Position* absPosition = (Position*)bullet->state->get("absolute_position");

        Position* position = (Position*)bullet->state->get("position");
        Trajectory* trajectory = (Trajectory*)bullet->state->get("trajectory");
        Color* color = (Color*)bullet->state->get("color");

        absPosition->horz += trajectory->position.horz;
        absPosition->vert += trajectory->position.vert;
        absPosition->depth += trajectory->position.depth;

        color->red = trajectory->color.red;
        color->green = trajectory->color.green;
        color->blue = trajectory->color.blue;
        color->alpha = trajectory->color.alpha;

        trajectory->color.red += ((1 + trajectory->color.red) * trajectory->colorRate.red) / 36;
        trajectory->color.green += ((1 + trajectory->color.green) * trajectory->colorRate.green) / 36;
        trajectory->color.blue += ((1 + trajectory->color.blue) * trajectory->colorRate.blue) / 36;
        trajectory->color.alpha += ((1 + trajectory->color.alpha) * trajectory->colorRate.alpha) / 36;

        if (trajectory->color.red > 255)    trajectory->color.red = 255;
        if (trajectory->color.blue > 255)   trajectory->color.blue = 255;
        if (trajectory->color.green > 255)  trajectory->color.green = 255;
        if (trajectory->color.alpha > 255)  trajectory->color.alpha = 255;

        if (absPosition->horz > scene->view->position.horz
          && absPosition->horz < (scene->view->position.horz + scene->view->size.horz)
          && absPosition->vert > scene->view->position.vert
          && absPosition->vert < (scene->view->position.vert + scene->view->size.vert)
        ) {
          // our bullet is visible within our screen.
          position->horz = (absPosition->horz - scene->view->position.horz);
          position->vert = (absPosition->vert - scene->view->position.vert);

        }

        if (absPosition->horz < 0
          || absPosition->vert < 0
          || absPosition->horz > scene->size->horz
          || absPosition->vert > scene->size->vert
        ) {
          // our bullet has left our space.

          bullet->isActive = false;
        }

        return (void*)NULL;
      }

  };

#endif
