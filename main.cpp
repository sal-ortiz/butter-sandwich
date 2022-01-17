
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "./src/runtime/window.hpp"
#include "./src/runtime/application.hpp"
#include "./src/runtime/image.hpp"
#include "./src/runtime/state.hpp"
#include "./src/scene/sprite.hpp"


Window* win = new Window();
Application* app = new Application();

State* state = new State();

//void* quitCallback(void*) {
////  printf("\n\nCALLED QUIT CALLBACK!!!!!!!!!\n\n");
//
//  return (void*)NULL;
//}

//void* closedCallback(void*) {
////  printf("\n\nCALLED WINDOW CLOSED CALLBACK!!!!!!!!!\n\n");
//
//  return (void*)NULL;
//}

//void* movedCallback(void*) {
////  printf("CALLED WINDOW MOVED CALLBACK!!");
//
//  return (void*)NULL;
//}

//void* resizedCallback(void*) {
////  printf("CALLED WINDOW RESIZED CALLBACK!!");
//
//  return (void*)NULL;
//}

void* getter(void* inp) {
  unsigned long int* val = reinterpret_cast<unsigned long int*>(inp);

  printf("\n\n\nit got GOT\t:::%lu:::\n", val);

  return (void*)777;
}

void* setter(void* inp) {
  unsigned long int* val = reinterpret_cast<unsigned long int*>(inp);

  printf("\n\n\nit got SET\t:::%lu:::\n", val);

  return (void*)888;
}

int main(int argc, char *argv[]) {
  unsigned long int* dummyVal;

//  app->on("QUIT", quitCallback, (void*)NULL);
//  win->on("CLOSED", closedCallback, (void*)NULL);
//  win->on("MOVED", movedCallback, (void*)NULL);
//  win->on("RESIZED", resizedCallback, (void*)NULL);

  state->onGet("CRAP", getter, (void*)NULL);
  state->onSet("CRAP", setter, (void*)NULL);

  state->set("CRAP", (void*)666);
  dummyVal = (unsigned long int*)state->get("CRAP");

  printf("\n\n%lu\n\n", (unsigned long int*)dummyVal);

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
