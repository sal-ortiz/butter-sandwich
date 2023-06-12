
#ifndef _DATA_ANGLE_HPP

  #define _DATA_ANGLE_HPP

  #include "./position.hpp"


  class Angle {

    public:

      float pitch;
      float roll;
      float yaw;

      Position center;

      Angle(
        float pitch=0.0,
        float roll=0.0,
        float yaw=0.0,

        float centerX=0.0,
        float centerY=0.0,
        float centerZ=0.0
      ) {

        this->pitch = pitch;
        this->roll = roll;
        this->yaw = yaw;

        this->center.horz = centerX;
        this->center.vert = centerY;
        this->center.depth = centerZ;
      }

  };

#endif
