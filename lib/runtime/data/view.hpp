
#ifndef _VIEW_HPP

  #define _VIEW_HPP

  #include <runtime/data/position.hpp>
  #include <runtime/data/size.hpp>

  class View {

    public:

      Position* position;
      Size* size;

      View() {
        this->position = new Position();
        this->size = new Size();
      }

  };

#endif
