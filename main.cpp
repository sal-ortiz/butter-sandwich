
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
  const char* action;

  if (parsedInp->state == SDL_PRESSED) {
    action = "pressed";
  } else if (parsedInp->state == SDL_RELEASED) {
    action = "released";
  }

  printf("Key %lu key %s at %lums\n", parsedInp->scancode, action, parsedInp->timestamp);

  return (void*)NULL;
}

void* mouseMotionCallback(void* inp) {
  MouseMotionEventParams* parsedInp = reinterpret_cast<MouseMotionEventParams*>(inp);

  printf("mouse moved to (%ld, %ld). (%ld, %ld) from it's previous location\n", parsedInp->absoluteHorzPos, parsedInp->absoluteVertPos, parsedInp->relativeHorzPos, parsedInp->relativeVertPos);

  return (void*)NULL;
}

void* mouseButtonCallback(void* inp) {
  MouseButtonEventParams* parsedInp = reinterpret_cast<MouseButtonEventParams*>(inp);
  const char* button;
  const char* action;

  if (parsedInp->state == SDL_PRESSED) {
    action = "pressed";
  } else if (parsedInp->state == SDL_RELEASED) {
    action = "released";
  }

  if (parsedInp->button == SDL_BUTTON_LEFT) {
    button = "left";
  } else if (parsedInp->button == SDL_BUTTON_MIDDLE) {
    button = "middle";

  } else if (parsedInp->button == SDL_BUTTON_RIGHT) {
    button = "right";
  }

  printf("%s mouse button %s %d times\n", button, action, parsedInp->clicks);

  return (void*)NULL;
}
void* getter(void* inp) {
  unsigned long int* parsedInp = reinterpret_cast<unsigned long int*>(inp);

  printf("value %lu gotten\n", (unsigned long int)parsedInp);

  return (void*)777;
}

void* setter(void* inp) {
  unsigned long int* parsedInp = reinterpret_cast<unsigned long int*>(inp);

  printf("value %lu set\n", (unsigned long int)parsedInp);

  return (void*)888;
}

int main(int argc, char *argv[]) {
  unsigned long int* dummyVal;

  app->on("QUIT", quitCallback, (void*)NULL);
  app->on("KEYBOARD", keyboardCallback, (void*)NULL);
  app->on("MOUSEMOTION", mouseMotionCallback, (void*)NULL);
  app->on("MOUSEBUTTON", mouseButtonCallback, (void*)NULL);
  win->on("CLOSED", closedCallback, (void*)NULL);
  win->on("MOVED", movedCallback, (void*)NULL);
  win->on("RESIZED", resizedCallback, (void*)NULL);

  state->onGet("CRAP", getter, (void*)NULL);
  state->onSet("CRAP", setter, (void*)NULL);

  state->set("CRAP", (void*)666);
  dummyVal = (unsigned long int*)state->get("CRAP");

  printf("\ndummyVal: %lu\n\n", (unsigned long int)dummyVal);

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


  unsigned long int numLoops = 0;
  unsigned long int elapsed = 0;

  unsigned long start = 0;

  while (app->isActive) {
    start = SDL_GetTicks();

    Event::evaluate();

    sprite->render(win->getRenderer(), 0, 0);

    win->render();

    elapsed += SDL_GetTicks() - start;

    if ((++numLoops % 100) == 0) {
      printf("\naverage frame time: %lums\n\n", elapsed / ++numLoops);
    }

  }

  //SDL_Delay(5000);

  delete app;
  delete win;

  SDL_Quit();
}
