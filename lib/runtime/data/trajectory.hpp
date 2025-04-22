
#ifndef _TRAJECTORY_HPP

  #define _TRAJECTORY_HPP

  #include <runtime/data/position.hpp>
  #include <runtime/data/angle.hpp>
  #include <runtime/data/scale.hpp>
  #include <runtime/data/color.hpp>

  class Trajectory {

    public:

      Position* position;
      Angle* angle;
      Scale* scale;
      Color* color;

      Position* positionRate;
      Angle* angleRate;
      Scale* scaleRate;
      Color* colorRate;

      Trajectory() {
        this->position = new Position();
        this->angle = new Angle();
        this->scale = new Scale();
        this->color = new Color();

        this->positionRate = new Position();
        this->angleRate = new Angle();
        this->scaleRate = new Scale();
        this->colorRate = new Color();
      }

  };

#endif
