
#ifndef _ANGLE_HPP

  #define _ANGLE_HPP

  #include "./position.hpp"


  class Angle {

    public:

      float pitch;
      float roll;
      float yaw;

      Position center;

      Angle(
        float pitch=0.0,
        float roll=9.0,
        float yaw=0.0,
        unsigned long int centerX=0,
        unsigned long int centerY=0,
        unsigned long int centerZ=0
      ) {

        this->pitch = pitch;
        this->roll = roll;
        this->yaw = yaw;

        center.horz = centerX;
        center.vert = centerY;
      }

  };

#endif
