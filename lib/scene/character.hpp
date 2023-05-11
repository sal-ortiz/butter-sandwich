
#ifndef _SCENE_CHARACTER_HPP

  #define _SCENE_CHARACTER_HPP

  #include "../scene/base.hpp"


  class SceneCharacter: public SceneBase {

    public:

      SceneCharacter() {
        this->type = "character";
      }

  };

#endif
