

#ifndef _SCENE_BASE_HPP_

  #define _SCENE_BASE_HPP_

  #include "../runtime/base.hpp"


  class SceneBase: public RuntimeBase {

    public:

      SceneBase() {
        this->generateIdentifier();
      }




  };



#endif
