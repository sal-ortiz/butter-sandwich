
#ifndef _POSITION_HPP

  #define _POSITION_HPP


  class Position {

    public:

      float horz;
      float vert;
      float depth;

      Position(
        float xPos=0.0,
        float yPos=0.0,
        float zPos=0.0
      ) {

        this->horz = xPos;
        this->vert = yPos;
        this->depth = zPos;
      }

  };

#endif
