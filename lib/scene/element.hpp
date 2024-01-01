
#ifndef _SCENE_ELEMENT_HPP

  #define _SCENE_ELEMENT_HPP

  #include "../scene/base.hpp"


  class SceneElement: public SceneBase {

    public:

      SceneElement() {
        this->type = "element";





        //this->onCollision(this->collisionCallback);





      }


      static void* collisionCallback(void* inpOne, void* inpTwo, void* inpThree) {
        printf("\n\n============================================");
        printf("\n==== COLLISION!!! ============================");
        printf("\n============================================\n\n");


        return NULL;
      }

  };

#endif
