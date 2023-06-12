
#ifndef _DATA_SIZE_HPP

  #define _DATA_SIZE_HPP


  class Size {

    public:

      float horz;
      float vert;
      float depth;

      Size(
        float width=0.0,
        float height=0.0,
        float depth=0.0
      ) {

        this->horz = width;;
        this->vert = height;
        this->depth = depth;
      }

  };

#endif


