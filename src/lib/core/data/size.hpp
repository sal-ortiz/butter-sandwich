
#ifndef _SIZE_HPP

  #define _SIZE_HPP


  class Size {

    public:

      unsigned long int horz;
      unsigned long int vert;
      unsigned long int depth;

      Size(
        unsigned long int width=0,
        unsigned long int height=0,
        unsigned long int depth=0
      ) {

        this->horz = width;;
        this->vert = height;
        this->depth = depth;
      }


  };

#endif


