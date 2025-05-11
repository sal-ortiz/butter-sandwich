
#ifndef _ANGLE_HPP

  #define _ANGLE_HPP

  #include <runtime/data/position.hpp>

  class Angle {

    public:

      Position* center;

      float pitch;
      float roll;
      float yaw;

      Angle() {
        this->center = new Position();

        this->pitch = 0;
        this->roll = 0;
        this->yaw = 0;
      }

      ~Angle() {
        delete this->center;
      }

  };

#endif
