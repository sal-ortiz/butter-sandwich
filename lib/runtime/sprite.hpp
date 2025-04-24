
#ifndef _SPRITE_HPP

  #define _SPRITE_HPP

  #include <stdint.h>

  #include <core/image.hpp>
  #include <core/list/binary_tree_list.hpp>
  #include <core/list/fixed_tree_list.hpp>
  #include <core/renderer.hpp>
  #include <runtime/sprite/frame.hpp>
  #include <runtime/data/position.hpp>
  #include <runtime/data/angle.hpp>
  #include <runtime/data/view.hpp>


  class Sprite {

    private:

      LinkedList<SpriteFrame*>* frames;
      //ArrayList<SpriteFrame*>* frames;

      Position position;
      uint32_t currentFrame;

      bool loop;


    public:

      float width;
      float height;

      Sprite() {
        this->frames = new LinkedList<SpriteFrame*>();
        //this->frames = new ArrayList<SpriteFrame*>();

        this->currentFrame = 0;

        this->position.horz = 0;
        this->position.vert = 0;

        this->loop = true;

        this->width = 0;
        this->height = 0;
      }

      ~Sprite() {
        uint32_t listLen = this->frames->getLength();

        for (uint32_t idx = 0; idx < listLen; idx++) {
          SpriteFrame* entry = this->frames->get(idx);

          delete entry;
        }

        delete this->frames;
      }

      void setLoop(bool value) {
        this->loop = value;
      }

      void addFrame(Image* img, uint32_t frameNum) {
        SpriteFrame* newFrame = new SpriteFrame();

        newFrame->setImage(img);

        newFrame->width = img->view.w;
        newFrame->height = img->view.h;

        this->frames->set(frameNum, newFrame);

        uint32_t numFrames = this->frames->getLength();
        uint32_t curFrameNum = frameNum + 1;

        SpriteFrame* curFrame = this->frames->get(curFrameNum);

        while (curFrameNum < (numFrames - 1) && curFrame != NULL) {

          if (curFrame == NULL) {
            SpriteFrame* newFrame = new SpriteFrame();

            newFrame->setImage(img);

            newFrame->width = img->view.w;
            newFrame->height = img->view.h;

            this->frames->set(curFrameNum, newFrame);
          }

          curFrame = this->frames->get(++curFrameNum);
        }

      }

      void render(Renderer *renderer, Position* dstPos, View* srcView, Angle* angle, Scale* scale, Color* color) {
        SpriteFrame* frame = this->nextFrame();

        frame->render(renderer, dstPos, srcView, angle, scale, color);
      }

      SpriteFrame* nextFrame() {
        uint32_t frameNum = this->currentFrame;

        SpriteFrame* frame = this->frames->get(frameNum);

        this->width = frame->width;
        this->height = frame->height;

        uint32_t numFrames = this->frames->getLength();

          this->currentFrame++;

        if (this->currentFrame >= numFrames) {
          this->currentFrame = this->currentFrame % numFrames;
        }

        return frame;
      }

      SpriteFrame* prevFrame() {
        if (this->currentFrame > 0) {
          this->currentFrame--;
        } else {
          this->currentFrame = this->frames->getLength() - 1;
        }

        return this->frames->get(this->currentFrame);
      }

  };

#endif
