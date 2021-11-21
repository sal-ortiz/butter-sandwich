
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "./src/runtime/window.hpp"
#include "./src/runtime/image.hpp"

#include "./src/sprite.hpp"


int main(int argc, char *argv[]) {

  Window* win = new Window();
  Sprite* sprite = new Sprite();

  win->open("The window!", 50, 50, 480, 360);

  Image* img = new Image();

  img->load("./img.bmp", 0, 0);
  sprite->addFrame(img);


  sprite->render(win->getRenderer(), 0, 0);

  win->render();

  SDL_Delay(5000);

  win->close();

}
