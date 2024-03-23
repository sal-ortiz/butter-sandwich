

#ifndef _COLOR_HPP

  #define _COLOR_HPP


  class Color {

    public:

      float red;
      float green;
      float blue;
      float alpha;

      Color(float red=255, float green=255, float blue=255, float alpha=255) {
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->alpha = alpha;
      }

  };

#endif
