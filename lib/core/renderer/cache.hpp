
#ifndef _RENDER_CACHE

  #define _RENDER_CACHE

  #include <SDL2/SDL.h>


  class RenderCache {

    public:

      SDL_Texture* texture;

      SDL_Rect src;
      SDL_Rect dst;
      SDL_Point center;
      SDL_Color color;

      float angle;

      RenderCache(SDL_Texture* texture, SDL_Rect src, SDL_Rect dst, SDL_Point center, float angle, SDL_Color color) {
        this->texture = texture;

        this->src = src;
        this->dst = dst;
        this->center = center;

        this->angle = angle;
        this->color = color;
      }

  };

#endif
