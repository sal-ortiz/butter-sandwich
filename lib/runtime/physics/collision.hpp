
#ifndef _PHYSICS_COLLISION_HPP

  #define _PHYSICS_COLLISION_HPP

  #include <SDL2/SDL.h>

  #include "../../scene.hpp"
  #include "../../scene/base.hpp"
  #include "./collision/tree.hpp"


  QuadNode* _collisionTree = NULL;

  // TODO: find a better way to store/populate these
  static float _collisionTreeWidth = 0;
  static float _collisionTreeHeight = 0;


  class Collision {

    public:

      static void insert(SceneBase* el) {

        if (_collisionTree == NULL) {
          _collisionTree = new QuadNode(_collisionTreeWidth, _collisionTreeHeight);
        }

        _collisionTree->insert(el);
      }

      static float getWidth() {
        return _collisionTreeWidth;
      }

      static void setWidth(float width) {
        _collisionTreeWidth = width;
      }

      static float getHeight() {
        return _collisionTreeHeight;
      }

      static void setHeight(float height) {
        _collisionTreeHeight = height;
      }

      static void evaluate() {
        _collisionTree->evaluate();

        delete _collisionTree;

        _collisionTree = NULL;
      }

  };

#endif
