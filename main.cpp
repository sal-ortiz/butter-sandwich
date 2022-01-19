
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "./src/runtime/window.hpp"
#include "./src/runtime/application.hpp"
#include "./src/runtime/image.hpp"
#include "./src/runtime/state.hpp"
#include "./src/runtime/sprite.hpp"


Window* win = new Window();
Application* app = new Application();

State* state = new State();

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

void* movedCallback(void* inp) {
  WindowEventParams* parsedInp = reinterpret_cast<WindowEventParams*>(inp);

  printf("Window moved to (%ld, %ld) at %lums\n", parsedInp->horz, parsedInp->vert, parsedInp->timestamp);

  return (void*)NULL;
}

void* resizedCallback(void* inp) {
  WindowEventParams* parsedInp = reinterpret_cast<WindowEventParams*>(inp);

  printf("Window resized to (%ld, %ld) at %lums\n", parsedInp->horz, parsedInp->vert, parsedInp->timestamp);

  return (void*)NULL;
}

void* keyboardCallback(void* inp) {
  KeyboardEventParams* parsedInp = reinterpret_cast<KeyboardEventParams*>(inp);
  char* action;

  if (parsedInp->state == SDL_PRESSED) {
    action = "pressed";
  } else if (parsedInp->state == SDL_RELEASED) {
    action = "released";
  }

  printf("Key %lu key %s at %lums\n", parsedInp->scancode, action, parsedInp->timestamp);

  return (void*)NULL;
}

void* getter(void* inp) {
  unsigned long int* parsedInp = reinterpret_cast<unsigned long int*>(inp);

  printf("value %lu gotten\n", parsedInp);

  return (void*)777;
}

void* setter(void* inp) {
  unsigned long int* parsedInp = reinterpret_cast<unsigned long int*>(inp);

  printf("value %lu set\n", parsedInp);

  return (void*)888;
}

int main(int argc, char *argv[]) {
  unsigned long int* dummyVal;

  app->on("QUIT", quitCallback, (void*)NULL);
  win->on("CLOSED", closedCallback, (void*)NULL);
  win->on("MOVED", movedCallback, (void*)NULL);
  win->on("RESIZED", resizedCallback, (void*)NULL);
  app->on("KEYBOARD", keyboardCallback, (void*)NULL);

  state->onGet("CRAP", getter, (void*)NULL);
  state->onSet("CRAP", setter, (void*)NULL);

  state->set("CRAP", (void*)666);
  dummyVal = (unsigned long int*)state->get("CRAP");

  printf("\n\n%lu\n\n", (unsigned long int*)dummyVal);

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
