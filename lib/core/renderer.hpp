
#ifndef _RENDERER_HPP

  #define _RENDERER_HPP

  #include <SDL2/SDL.h>

  #include "./renderer/cache.hpp"
  #include "./dict.hpp"


  class Renderer {

    private:

      SDL_Renderer* renderer;

      //Dict<RenderCache*>* cache;


    public:

      Renderer(SDL_Window* winHandle) {
        uint32_t flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

        //this->cache = new Dict<RenderCache*>();
        this->renderer = SDL_CreateRenderer(winHandle, -1, flags);
      }

      ~Renderer() {

        //// used for selective rendering
        //List<RenderCache*>* cacheList = this->cache->getValues();
        //
        //unsigned long int cacheLen = cacheList->getLength();
        //
        //for (unsigned long int cacheIdx = 0; cacheIdx < cacheLen; cacheIdx++) {
        //  RenderCache* entry = cacheList->get(cacheIdx);
        //
        //  delete entry;
        //}
        //
        //delete cacheList;
        //delete this->cache;

        SDL_DestroyRenderer(this->renderer);
      }

      SDL_Renderer* getRenderer() {
        return this->renderer;
      }

      void clear() {
        SDL_RenderClear(this->renderer);
      }

      void present() {
        SDL_RenderPresent(this->renderer);
      }

      //void render(
      //  unsigned long int identifier,
      //  SDL_Texture* texture,
      //  uint32_t dstX,
      //  uint32_t dstY,
      //  uint32_t dstWidth,
      //  uint32_t dstHeight,
      //  uint32_t srcX,
      //  uint32_t srcY,
      //  uint32_t srcWidth,
      //  uint32_t srcHeight,
      //  float dstAngle=0.0,
      //  uint32_t centerX=0,
      //  uint32_t centerY=0
      //) {
      //  // selective rendering
      //  char idStr[11];
      //
      //  sprintf(idStr, "%10.lu", identifier);
      //
      //  RenderCache* entry = this->cache->get(idStr);
      //
      //  if (
      //    entry == NULL ||
      //    (entry->dstX != dstX) ||
      //    (entry->dstY != dstY) ||
      //    (entry->dstWidth != dstWidth) ||
      //    (entry->dstHeight != dstHeight) ||
      //    (entry->srcX != srcX) ||
      //    (entry->srcY != srcY) ||
      //    (entry->srcWidth != srcWidth) ||
      //    (entry->srcHeight != srcHeight) ||
      //    (entry->dstAngle != dstAngle) ||
      //    (entry->centerX != centerX) ||
      //    (entry->centerY != centerY)
      //  ) {
      //
      //    this->render(
      //      texture,
      //      dstX, dstY, dstWidth, dstHeight,
      //      srcX, srcY, srcWidth, srcHeight,
      //      dstAngle, centerX, centerY
      //    );
      //
      //    RenderCache* newEntry = new RenderCache(
      //      identifier,
      //      dstX, dstY, dstWidth, dstHeight,
      //      srcX, srcY, srcWidth, srcHeight,
      //      dstAngle, centerX, centerY
      //    );
      //
      //    this->cache->set(idStr, newEntry);
      //  }
      //
      //}

      void render(
        SDL_Texture* texture,
        uint32_t dstX,
        uint32_t dstY,
        uint32_t dstWidth,
        uint32_t dstHeight,
        uint32_t srcX,
        uint32_t srcY,
        uint32_t srcWidth,
        uint32_t srcHeight,
        float dstAngle=0.0,
        uint32_t centerX=0,
        uint32_t centerY=0
      ) {
        // TODO: Instead of rendering here, we should track everything that
        //       needs to be rendered and wait until we're presenting
        //       to actually render. That way we can isolate the regions
        //       of the screen where changes are to be rendered and not
        //       render the whole screen every time.

        SDL_Rect srcRect = {
          (uint16_t)srcX,
          (uint16_t)srcY,
          (uint16_t)srcWidth,
          (uint16_t)srcHeight
        };

        SDL_Point center = {
          (uint16_t)centerX,
          (uint16_t)centerY
        };

        SDL_Rect dstRect = {
          (uint16_t)dstX,
          (uint16_t)dstY,
          (uint16_t)dstWidth,
          (uint16_t)dstHeight
        };

        SDL_RenderCopyEx(this->renderer, texture, &srcRect, &dstRect, dstAngle, &center, SDL_FLIP_NONE);
      }

  };

#endif
