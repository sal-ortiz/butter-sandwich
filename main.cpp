


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

static bool quitCallback(void* inp) {
  printf("QUITTING!!!!\t%ld\n", *(unsigned long int*)inp);

  return false;
}


int main(int argc, char *argv[]) {
  bool isRunning = true;

  unsigned long int inp = 0;

  app->on("CLOSE", quitCallback, &inp);
  app->on("QUIT", quitCallback, &inp);

  inp = 666;

  Sprite* sprite = new Sprite();

  win->open("The window!", 50, 50, 480, 360);

  Image* imgOne = new Image();
  Image* imgTwo = new Image();

  imgOne->load("./img1.bmp", 0, 0);
  imgTwo->load("./img2.bmp", 0, 0);

//  sprite->setLoop(false);

  sprite->addFrame(imgOne, 0);
  sprite->addFrame(imgTwo, 150);
  sprite->addFrame(200);

  while (app->evaluate()) {
    sprite->render(win->getRenderer(), 0, 0);

    win->render();
  }

  //SDL_Delay(5000);

  delete win;

  SDL_Quit();
}
