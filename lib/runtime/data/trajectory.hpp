
#ifndef _TRAJECTORY_HPP

  #define _TRAJECTORY_HPP

  #include "./position.hpp"
  #include "./angle.hpp"
  #include "./scale.hpp"
  #include "./color.hpp"


  class Trajectory {

    public:

      Position position;
      Angle angle;
      Scale scale;
      Color color;

      Position positionRate;
      Angle angleRate;
      Scale scaleRate;
      Color colorRate;

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

        this->colorRate.red = 255.0;
        this->colorRate.green = 255.0;
        this->colorRate.blue = 255.0;
        this->colorRate.alpha = 255.0;
      }

  };

#endif
