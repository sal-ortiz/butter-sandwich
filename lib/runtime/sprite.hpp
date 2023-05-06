
#ifndef _SPRITE_HPP

  #define _SPRITE_HPP

  #include "../core/image.hpp"
  #include "../core/list.hpp"
  #include "./sprite/frame.hpp"
  #include "./data/position.hpp"
  #include "./data/angle.hpp"
  #include "./data/view.hpp"


  class Sprite {

    private:

      List<SpriteFrame*>* frames;
      List<uint32_t>* framesList;

      Position position;
      uint32_t currentFrame;

      bool loop;


      void normalizeFramesList() {
        uint32_t lastRenderedFrame = -1;
        uint32_t framesListLen = this->framesList->getLength();

        for (uint32_t idx = 0; idx < framesListLen; idx++) {
          uint32_t curFrame = this->framesList->get(idx);

          if (curFrame < framesListLen) {
            lastRenderedFrame = this->framesList->get(idx);
          }

          this->framesList->set(idx, lastRenderedFrame);
        }

      }


    public:

      float width;
      float height;


      Sprite() {
        this->frames = new List<SpriteFrame*>();
        this->framesList = new List<uint32_t>();

        this->currentFrame = 0;

        this->position.horz = 0;
        this->position.vert = 0;

        this->loop = true;

        this->width = 0;
        this->height = 0;
      }

      void setLoop(bool value) {
        this->loop = value;
      }

      //void jumpToFrame(uint32_t frameNum) {
      //  this->currentFrame = frameNum;
      //}

      void addFrame(unsigned int frameNum) {
        framesList->set(frameNum, frames->getLength() - 1);

        this->normalizeFramesList();
      }

      void addFrame(Image* img, unsigned int frameNum) {
        // NOTE: The first frasme *must* begin at index 0.

        if (frames->getLength() > 0) {
          unsigned int curFrame = this->currentFrame;
          uint32_t frameRef = this->framesList->get(curFrame);

          SpriteFrame* frame = this->frames->get(frameRef);

          this->width = frame->width;
          this->height = frame->height;

        } else {
          this->width = img->view.w;
          this->height = img->view.h;

        }

        SpriteFrame* newFrame = new SpriteFrame();

        newFrame->setImage(img);
        frames->push(newFrame);
        framesList->set(frameNum, frames->getLength() - 1);

        this->normalizeFramesList();
      }

      void render(SDL_Renderer *renderer, Position* dstPos, View* srcView, Angle* angle) {
        SpriteFrame* frame = this->nextFrame();

        frame->render(renderer, *dstPos, *srcView, *angle);
      }

      SpriteFrame* nextFrame() {
        uint32_t idx = this->currentFrame;
        uint32_t frameRef = this->framesList->get(idx);

        SpriteFrame* frame = this->frames->get(frameRef);

        if (this->currentFrame < (this->framesList->getLength() - 1)) {
          this->currentFrame = (this->currentFrame + 1);

        } else if (this->loop == true) {
          this->currentFrame = this->currentFrame % (this->framesList->getLength() - 1);

        }

        this->width = frame->width;
        this->height = frame->height;

        return frame;
      }

      SpriteFrame* prevFrame() {
        if (this->currentFrame == 0) {
          this->currentFrame = this->frames->getLength() - 1;
        } else {
          this->currentFrame--;
        }

        return this->frames->get(this->currentFrame);
      }

  };

#endif
