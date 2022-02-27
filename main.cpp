
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "./src/lib/runtime/window.hpp"
#include "./src/lib/runtime/application.hpp"
#include "./src/lib/core/image.hpp"
#include "./src/lib/runtime/sprite.hpp"

#include "./src/lib/scene/character.hpp"


Window* win = new Window();
Application* app = new Application();

SceneCharacter* character = new SceneCharacter();



void* quitCallback(void* inp) {
  ApplicationEventParams* parsedInp = reinterpret_cast<ApplicationEventParams*>(inp);

  printf("Quitting application at %lums\n", parsedInp->timestamp);

  return (void*)NULL;
}

void* closedCallback(void* inp) {
  WindowEventParams* parsedInp = reinterpret_cast<WindowEventParams*>(inp);

  printf("Window closed at %ldms\n", parsedInp->timestamp);

  return (void*)NULL;
}

int main(int argc, char *argv[]) {
  unsigned long int* dummyVal;

  app->on("QUIT", quitCallback, (void*)NULL);
  win->on("CLOSED", closedCallback, (void*)NULL);

  Sprite* sprite = new Sprite();

  win->open("The window!", 150, 150, 480, 360);

  Image* imgOne = new Image();
  Image* imgTwo = new Image();

  imgOne->load("./img1.bmp", 0, 0);
  imgTwo->load("./img2.bmp", 0, 0);

//  sprite->setLoop(false);

  sprite->addFrame(imgOne, 0);
  sprite->addFrame(imgTwo, 150);
  sprite->addFrame(200);

  character->addSprite("standing", sprite);

  app->start();

  unsigned long int numLoops = 0;
  float start = 0.0;
  float elapsed = 0.0;

  while (app->isActive) {
    start = (float)SDL_GetTicks();

    Event::evaluate();

    character->render("standing", win->getRenderer());

    win->render();

    elapsed += (float)SDL_GetTicks() - start;

    if ((++numLoops % 500) == 0) {
      printf("\naverage frame time: %fms\n\n", elapsed / numLoops);
    }

  }

  //SDL_Delay(5000);

  delete app;
  delete win;

  SDL_Quit();
}
