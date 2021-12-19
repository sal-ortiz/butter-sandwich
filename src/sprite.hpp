

#ifndef _SPRITE_HPP
  #define _SPRITE_HPP

  #include "./frame.hpp"
  #include "./core/list.hpp"


  struct Position {
    uint32_t horz;
    uint32_t vert;
    float scale;
  };

  class Sprite {

    private:

      List<SpriteFrame*>* frames;

      Position position;
      uint32_t currentFrame;

    public:

      Sprite() {
        this->frames = new List<SpriteFrame*>();

        position.horz = 0;
        position.vert = 0;
      }

      void addFrame(Image* img) {
        SpriteFrame* newFrame = new SpriteFrame(img);

        frames->push(newFrame);
      }

      void render(SDL_Renderer* renderer, uint32_t dstX, uint32_t dstY) {
        SpriteFrame* frame = this->nextFrame();

        frame->render(renderer, dstX, dstY);
      }

      SpriteFrame* nextFrame() {
        uint32_t idx = this->currentFrame;

        this->currentFrame = (currentFrame + 1) % this->frames->getLength();

        return this->frames->get(idx);
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
