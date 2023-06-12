
#ifndef _SCALE_HPP

  #define _SCALE_HPP


  class Scale {

    public:

      float horz;
      float vert;
      float depth;

      Scale(
        float xScale=1.0,
        float yScale=1.0,
        float zScale=1.0
      ) {

        this->horz = xScale;
        this->vert = yScale;
        this->depth = zScale;
      }

  };

#endif
