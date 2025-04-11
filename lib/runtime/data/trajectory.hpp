
#ifndef _TRAJECTORY_HPP

  #define _TRAJECTORY_HPP

  #include <runtime/data/position.hpp>
  #include <runtime/data/angle.hpp>
  #include <runtime/data/scale.hpp>
  #include <runtime/data/color.hpp>

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
