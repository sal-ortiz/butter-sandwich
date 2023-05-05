
#ifndef _TRAJECTORY_HPP

  #define _TRAJECTORY_HPP

  #include "./position.hpp"
  #include "./angle.hpp"
  #include "./scale.hpp"


  class Trajectory {

    public:

      Position position;
      Angle angle;
      Scale scale;

      Position positionRate;
      Angle angleRate;
      Scale scaleRate;

      Trajectory() {
        this->positionRate.horz = 1.0;
        this->positionRate.vert = 1.0;
        this->positionRate.depth = 1.0;

        this->angleRate.pitch = 1.0;
        this->angleRate.roll = 1.0;
        this->angleRate.yaw = 1.0;

        this->scaleRate.horz = 1.0;
        this->scaleRate.vert = 1.0;
        this->scaleRate.depth = 1.0;
      }

  };

#endif
