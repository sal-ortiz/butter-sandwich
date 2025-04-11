
#ifndef _ANGLE_HPP

  #define _ANGLE_HPP

  #include <runtime/data/position.hpp>

  struct Angle {
    Position center;

    float pitch = 0;
    float roll = 0;
    float yaw = 0;
  };

#endif
