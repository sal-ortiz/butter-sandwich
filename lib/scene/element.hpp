
#ifndef _SCENE_ELEMENT_HPP

  #define _SCENE_ELEMENT_HPP

  #include <scene/base.hpp>


  class SceneElement: public SceneBase {

    public:

      SceneElement() {
        this->type = "element";
      }
  };

#endif
