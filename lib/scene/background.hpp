
#ifndef _SCENE_BACKGROUND_HPP

  #define _SCENE_BACKGROUND_HPP

  #include "../scene/base.hpp"


  class SceneBackground: public SceneBase {

    public:

      SceneBackground() {
        this->type = "background";
      }

  };

#endif
