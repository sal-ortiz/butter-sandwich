


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "./src/runtime/window.hpp"
#include "./src/runtime/image.hpp"
#include "./src/runtime/event.hpp"
#include "./src/application.hpp"

#include "./src/sprite.hpp"

#include "./src/core/dict.hpp"


Window* win = new Window();
Application* app = new Application();


int main(int argc, char *argv[]) {
  bool isRunning = true;

  Sprite* sprite = new Sprite();

  win->open("The window!", 50, 50, 480, 360);

  Image* imgOne = new Image();
  Image* imgTwo = new Image();

  imgOne->load("./img.bmp", 0, 0);
  imgTwo->load("./img2.bmp", 0, 0);

  sprite->addFrame(imgOne, 0);
  sprite->addFrame(imgTwo, 5);
  sprite->addFrame(10);

  while (app->evaluate()) {
    sprite->render(win->getRenderer(), 0, 0);

    win->render();
  }

  //SDL_Delay(5000);

  delete win;

  SDL_Quit();
}