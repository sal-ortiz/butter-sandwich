
#ifndef _RENDER_CACHE

  #define _RENDER_CACHE

  #include <SDL2/SDL.h>


  class RenderCache {

    public:

      SDL_Texture* texture;

      SDL_Rect src;
      SDL_Rect dst;
      SDL_Point center;

      float angle;

      RenderCache(SDL_Texture* texture, SDL_Rect src, SDL_Rect dst, SDL_Point center, float angle) {
        this->texture = texture;

        this->src = src;
        this->dst = dst;
        this->center = center;

        this->angle = angle;
      }

  };

#endif
