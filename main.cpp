
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "./src/runtime/window.hpp"
#include "./src/runtime/application.hpp"
#include "./src/runtime/image.hpp"
#include "./src/runtime/state.hpp"
#include "./src/scene/sprite.hpp"


Window* win = new Window();
Application* app = new Application();

void* quitCallback(void*) {
  printf("\n\nCALLED QUIT CALLBACK!!!!!!!!!\n\n");

  return (void*)NULL;
}

void* closedCallback(void*) {
  printf("\n\nCALLED WINDOW CLOSED CALLBACK!!!!!!!!!\n\n");

  return (void*)NULL;
}
void* movedCallback(void*) {
  printf("CALLED WINDOW MOVED CALLBACK!!");

  return (void*)NULL;
}

void* resizedCallback(void*) {
  printf("CALLED WINDOW RESIZED CALLBACK!!");

  return (void*)NULL;
}


int main(int argc, char *argv[]) {
  bool isRunning = true;

  app->on("QUIT", quitCallback, (void*)NULL);
  win->on("CLOSED", closedCallback, (void*)NULL);
  win->on("MOVED", movedCallback, (void*)NULL);
  win->on("RESIZED", resizedCallback, (void*)NULL);

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

  app->start();

  while (app->isActive) {
    Event::evaluate();

    sprite->render(win->getRenderer(), 0, 0);

    win->render();
  }

  //SDL_Delay(5000);

  delete app;
  delete win;

  SDL_Quit();
}
