
#ifndef _VIEW_HPP

  #define _VIEW_HPP

  #include "./position.hpp"
  #include "./size.hpp"


  class View {

    public:

      Position position;
      Size size;

      View(
        float xPos=0.0,
        float yPos=0.0,
        float zPos=0.0,
        float width=0.0,
        float height=0.0,
        float depth=0.0
      ) {

        this->position.horz = xPos;
        this->position.vert = yPos;
        this->position.depth = zPos;

        this->size.horz = width;
        this->size.vert = height;
        this->size.depth = depth;
      }

  };

#endif
