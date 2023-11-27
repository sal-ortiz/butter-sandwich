
#ifndef _RENDERER_HPP

  #define _RENDERER_HPP

  #include <SDL2/SDL.h>

  #include "./renderer/cache.hpp"
  #include "./dict.hpp"


  class Renderer {

    private:

      SDL_Renderer* renderer;

      List<RenderCache*>* cache;

      void emptyCache() {
        uint32_t len = this->cache->getLength();

        for (uint32_t idx = 0; idx < len; idx++) {
          RenderCache* entry = this->cache->get(idx);

          delete entry;
        }

      }

      void renderCache() {
        uint32_t len = this->cache->getLength();

        for (uint32_t idx = 0; idx < len; idx++) {
          RenderCache* entry = this->cache->get(idx);

          SDL_RenderCopyEx(
            this->renderer,
            entry->texture,
            &(entry->src),
            &(entry->dst),
            entry->angle,
            &(entry->center),
            SDL_FLIP_NONE
          );

        }

      }


    public:

      Renderer(SDL_Window* winHandle) {
        uint32_t flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

        this->renderer = SDL_CreateRenderer(winHandle, -1, flags);
        this->cache = new List<RenderCache*>();
      }

      ~Renderer() {
        SDL_DestroyRenderer(this->renderer);

        this->emptyCache();
        delete this->cache;
      }

      SDL_Renderer* getRenderer() {
        return this->renderer;
      }

      void clear() {
        SDL_RenderClear(this->renderer);
      }

      void present() {
        this->renderCache();

        SDL_RenderPresent(this->renderer);

        this->emptyCache();
        delete this->cache;

        this->cache = new List<RenderCache*>();
      }

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

        RenderCache* newEntry = new RenderCache(texture, srcRect, dstRect, center, dstAngle);

        this->cache->push(newEntry);
      }

  };

#endif
