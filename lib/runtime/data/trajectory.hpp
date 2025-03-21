
#ifndef _TRAJECTORY_HPP

  #define _TRAJECTORY_HPP

  #include "./position.hpp"
  #include "./angle.hpp"
  #include "./scale.hpp"
  #include "./color.hpp"

  struct Trajectory {
    Position position;
    Angle angle;
    Scale scale;
    Color color;

    Position positionRate;
    Angle angleRate;
    Scale scaleRate;
    Color colorRate;
  };

#endif
