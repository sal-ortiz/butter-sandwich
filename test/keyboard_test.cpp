

#include "../lib/core/keyboard.hpp"
#include <time.h>
#include <stdio.h>
#include <cstddef>


int main(int argc, char* argv[]) {
  KeyboardInput::initialize();

  printf("\n\n====================================================\n");

  KeyboardInput::setState(77, true);
  KeyboardInput::setState(78, true);
  KeyboardInput::setState(79, true);
  KeyboardInput::setState(80, true);
  KeyboardInput::setState(81, true);
  KeyboardInput::setState(82, true);
  KeyboardInput::setState(83, true);

  //printf("[%ld] %d: %d\n", time(0), 76, KeyboardInput::getState(76)->isPressed);
  //printf("[%ld] %d: %d\n", time(0), 77, KeyboardInput::getState(77)->isPressed);
  //printf("[%ld] %d: %d\n", time(0), 78, KeyboardInput::getState(78)->isPressed);
  //printf("[%ld] %d: %d\n", time(0), 79, KeyboardInput::getState(79)->isPressed);
  //printf("[%ld] %d: %d\n", time(0), 80, KeyboardInput::getState(80)->isPressed);
  //printf("[%ld] %d: %d\n", time(0), 81, KeyboardInput::getState(81)->isPressed);
  //printf("[%ld] %d: %d\n", time(0), 82, KeyboardInput::getState(82)->isPressed);
  //printf("[%ld] %d: %d\n", time(0), 83, KeyboardInput::getState(83)->isPressed);
  //printf("[%ld] %d: %d\n", time(0), 84, KeyboardInput::getState(84)->isPressed);

  printf("[%ld] %d: %d\n", time(0), 76, KeyboardInput::isPressed(76));
  printf("[%ld] %d: %d\n", time(0), 77, KeyboardInput::isPressed(77));
  //printf("[%ld] %d: %d\n", time(0), 78, KeyboardInput::isPressed(78));
  printf("[%ld] %d: %d\n", time(0), 79, KeyboardInput::isHeld(79));
  printf("[%ld] %d: %d\n", time(0), 80, KeyboardInput::isHeld(80));
  printf("[%ld] %d: %d\n", time(0), 81, KeyboardInput::isHeld(81));
  //printf("[%ld] %d: %d\n", time(0), 82, KeyboardInput::isPressed(82));
  printf("[%ld] %d: %d\n", time(0), 83, KeyboardInput::isReleased(83));
  printf("[%ld] %d: %d\n", time(0), 84, KeyboardInput::isReleased(84));

  printf("\n====================================================\n\n");

  KeyboardInput::deinitialize();
}
