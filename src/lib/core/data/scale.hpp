
#ifndef _SCALE_HPP

  #define _SCALE_HPP


  class Scale {

    public:

      float horz;
      float vert;
      float depth;

      Scale(
        float xScale=0.0,
        float yScale=0.0,
        float zScale=0.0
      ) {

        this->horz = xScale;
        this->vert = yScale;
        this->depth = zScale;
      }




  };

#endif
