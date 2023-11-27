
#ifndef _SPRITE_FRAME_HPP

  #define _SPRITE_FRAME_HPP

  #include "../../core/image.hpp"
  #include "../../core/renderer.hpp"
  #include "../data/position.hpp"
  #include "../data/view.hpp"
  #include "../data/angle.hpp"
  #include "../data/scale.hpp"


  class SpriteFrame {

    private:

      Image* image;


    public:

      float width;
      float height;

      SpriteFrame() {
        this->image = NULL;
      }

      void render(Renderer* renderer, Position dstPos, View srcView, Angle angle, Scale scale) {

        if (this->image) {

          this->image->render(
            renderer,
            dstPos.horz,
            dstPos.vert,
            scale.horz,
            scale.vert,
            srcView.position.horz,
            srcView.position.vert,
            srcView.size.horz,
            srcView.size.vert,
            angle.pitch,
            angle.center.horz,
            angle.center.vert
          );

        }

      }

      void setImage(Image* img) {
        this->image = img;

        this->width = img->view.w;
        this->height = img->view.h;
      }

      Image* getImage() {
        return this->image;
      }

  };

#endif
