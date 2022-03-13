
#ifndef _POSITION_HPP

  #define _POSITION_HPP


  class Position {

    public:

      unsigned long int horz;
      unsigned long int vert;
      unsigned long int depth;

      Position(
        unsigned long int xPos=0,
        unsigned long int yPos=0,
        unsigned long int zPos=0
      ) {

        this->horz = xPos;
        this->vert = yPos;
        this->depth = zPos;
      }

  };

#endif
