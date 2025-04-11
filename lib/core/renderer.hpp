
#ifndef _RENDERER_HPP

  #define _RENDERER_HPP

  #include <stdint.h>

  #include <SDL2/SDL.h>

  #include <core/list/linked_list.hpp>
  #include <core/renderer/cache.hpp>


  class Renderer {

    private:

      SDL_Renderer* renderer;

      LinkedList<RenderCache*>* cache;

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
          RenderCache* entry = this->cache->shift();

          SDL_SetTextureColorMod(
            entry->texture,
            entry->color.r,
            entry->color.g,
            entry->color.b
          );

          SDL_SetTextureAlphaMod(entry->texture, entry->color.a);

          SDL_RenderCopyEx(
            this->renderer,
            entry->texture,
            &(entry->src),
            &(entry->dst),
            entry->angle,
            &(entry->center),
            SDL_FLIP_NONE
          );

          SDL_SetTextureColorMod(entry->texture, 255, 255, 255);
          SDL_SetTextureAlphaMod(entry->texture, 255);

          delete entry;
        }

      }


    public:

      Renderer(SDL_Window* winHandle) {
        uint32_t flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

        this->renderer = SDL_CreateRenderer(winHandle, -1, flags);
        this->cache = new LinkedList<RenderCache*>();
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
        uint32_t centerY=0,
        uint8_t red=255,
        uint8_t green=255,
        uint8_t blue=255,
        uint8_t alpha=255
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

        SDL_Color color = {
          (uint8_t)red,
          (uint8_t)green,
          (uint8_t)blue,
          (uint8_t)alpha
        };

        RenderCache* newEntry = new RenderCache(texture, srcRect, dstRect, center, dstAngle, color);

        this->cache->push(newEntry);
      }

  };

#endif
