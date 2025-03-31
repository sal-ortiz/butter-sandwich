

#include <time.h>
#include <stdio.h>
#include <cstddef>

#include "../lib/core/list/linked_list.hpp"
#include "../lib/core/list/binary_tree_list.hpp"
#include "../lib/core/list/fixed_tree_list.hpp"
#include "../lib/core/list/array_list.hpp"


int main(int argc, char* argv[]) {

  //LinkedList<const char*>* list = new LinkedList<const char*>();
  //FixedTreeList<const char*>* list = new FixedTreeList<const char*>();
  ArrayList<const char*>* list = new ArrayList<const char*>();
  //BinaryTreeList<const char*>* list = new BinaryTreeList<const char*>();

  time_t timestamp = time(0);

  //printf("\n\n====================================================");

  printf("\n");

  list->set(4, "four");
  list->set(6, "six");
  list->set(0, "zero");
  list->set(7, "seven");
  list->set(3, "three");
  list->set(2, "two");
  list->set(1, "one");
  list->set(5, "five");
  list->set(8, "eight");
  list->set(7, "seven");
  list->set(12, "twelve");
  list->set(6, "six");

  //list->set(65535, "six-five-five-three-five");

  list->push("crap");
  list->push("shit");
  list->push("poot");
  list->push("poop");
  list->push("crappity");
  list->push("assy");
  list->push("shitty");

  list->unshift("crap");
  list->unshift("shit");
  list->unshift("poot");
  list->unshift("poop");
  list->unshift("crappity");
  list->unshift("assy");
  list->unshift("shitty");



  for (uint32_t idx = 0; idx < 4096; idx++) {
    char* str = (char*)malloc(8);

    sprintf(str, "%d", idx);

    list->set(idx, str);
  }


  //printf("\n================================================\n");

//  for (uint32_t idx = 0; idx < list->getLength(); idx++) {
//    printf("\n[%ld] INDEX %d: %s\n\n", time(0), idx, list->get(idx));
//  }

//  list->set(16, "xxx");
//
//  printf("\n[%ld] LIST SIZE AT START: %u", timestamp, list->getLength());
//


  //printf("\n[%ld] INDEX %d: %s\n\n", time(0), 2, list->get(2));
//  printf("\n----------------------------------------------------");
//  printf("\n[%ld] INDEX %d / %d: %s", time(0), 0, list->getLength(), list->get(0));
//  printf("\n[%ld] INDEX %d / %d: %s", time(0), 1, list->getLength(), list->get(1));
//  printf("\n[%ld] INDEX %d / %d: %s", time(0), 2, list->getLength(), list->get(2));
//  printf("\n[%ld] INDEX %d / %d: %s", time(0), 3, list->getLength(), list->get(3));
//  printf("\n[%ld] INDEX %d / %d: %s", time(0), 4, list->getLength(), list->get(4));
//  printf("\n[%ld] INDEX %d / %d: %s", time(0), 5, list->getLength(), list->get(5));
//  printf("\n[%ld] INDEX %d / %d: %s", time(0), 6, list->getLength(), list->get(6));
//  printf("\n[%ld] INDEX %d / %d: %s", time(0), 7, list->getLength(), list->get(7));
//  printf("\n[%ld] INDEX %d / %d: %s", time(0), 8, list->getLength(), list->get(8));
//  printf("\n[%ld] INDEX %d / %d: %s", time(0), 9, list->getLength(), list->get(9));
//  printf("\n[%ld] INDEX %d / %d: %s", time(0), 10, list->getLength(), list->get(10));
//  printf("\n[%ld] INDEX %d / %d: %s", time(0), 11, list->getLength(), list->get(11));
//  printf("\n[%ld] INDEX %d / %d: %s", time(0), 12, list->getLength(), list->get(12));
  printf("\n----------------------------------------------------");
  //printf("\n[%ld] INDEX %d: %s\n\n", time(0), 5, list->get(5));

  //printf("\n================================================\n");

  printf("\n\n");
//  printf("\n%s", list->shift());
//  printf("\n%s", list->shift());
//  printf("\n%s", list->shift());
//  printf("\n%s", list->shift());
//  printf("\n%s", list->shift());
//  printf("\n%s", list->shift());

  printf("\n");

//  printf("\n%s", list->pop());
//  printf("\n%s", list->pop());
//  printf("\n%s", list->pop());
//  printf("\n%s", list->pop());
//  printf("\n%s", list->pop());
//  printf("\n%s", list->pop());

  //list->remove(1);

  printf("\n\n");

  for (uint32_t idx = 0; idx < list->getLength(); idx++) {
    printf("\n[%ld] INDEX %d: %s", time(0), idx, list->get(idx));
  }

//    printf("\n[%ld] INDEX %d: %s", time(0), list->getLength() - 1, list->get(list->getLength() - 1));

//  printf("\n[%ld] LIST SIZE AT END: %u", timestamp, list->getLength());
//  printf("\n====================================================\n\n");
//
//
//  printf("\n[%ld] INDEX 19: %s", timestamp, list->get(19));
//  printf("\n[%ld] INDEX 20: %s", timestamp, list->get(20));

  printf("\n");

  delete list;
}
