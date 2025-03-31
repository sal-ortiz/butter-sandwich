
#include "../lib/core/quadtree.hpp"


int main(int argc, char* argv[]) {

  Quadtree<const char*>* tree = new Quadtree<const char*>(1920, 1080);


  tree->insert(99, 99, 20, 20, "one");
  tree->insert(101, 100, 10, 10, "two");
  tree->insert(101, 100, 10, 10, "three");
  tree->insert(100, 100, 10, 10, "four");
//  tree->insert(101, 100, 10, 10, "five");
  tree->insert(111, 400, 10, 10, "six");
  tree->insert(121, 401, 10, 10, "seven");
//  tree->insert(666, 100, 10, 10, "eight');
  tree->insert(322, 120, 10, 10, "nine");
  tree->insert(333, 130, 10, 10, "ten");
  tree->insert(676, 200, 10, 10, "eleven");
  tree->insert(670, 190, 1, 1, "twelve");

  //tree->insert(444, 140, 140);
  //tree->insert(555, 150, 150);
  //tree->insert(666, 160, 160);
  //tree->insert(777, 170, 170);

  //printf("one: %d\n", tree->query(155, 165/*, 10, 10*/));
  //printf("two; %d\n", tree->query(100, 100/*, 10, 10*/));


//  printf("\n\n");
//
  //printf("\n\n\n================[ OUTPUT ]======================");
  //LinkedList<QuadtreeElement<const char*>*>* list = tree->query(320, 115, 10, 10);
  //LinkedList<QuadtreeElement<const char*>*>* list = tree->query(674, 195, 20, 20);
  //LinkedList<QuadtreeElement<const char*>*>* list = tree->query(100, 100, 20, 20);
  //LinkedList<QuadtreeElement<const char*>*>* list = tree->query(90, 90, 20, 20);
  //LinkedList<QuadtreeElement<const char*>*>* list = tree->query(166, 100, 10, 10);
  LinkedList<QuadtreeElement<const char*>*>* list = tree->query(50, 50, 10, 10);
  //LinkedList<QuadtreeElement<const char*>*>* list = tree->query(675, 199, 5, 5);

  //for (uint16_t horzOffset = 0; horzOffset < 1000; horzOffset++) {
  //  LinkedList<QuadtreeElement<const char*>*>* list = tree->query(670 + horzOffset, 200, 10, 10);
  //
  //  if (list->getLength() > 0) {
  //    printf("\n==========[ %d", horzOffset);
  //  }
  //
  //}

  //printf("\n\n****** SHOULD RETURN ENTRY *****");
  //printf("\npopdList->getLength(): %d\n", list->getLength());

  for (uint32_t idx = 0; idx < list->getLength(); idx++) {
    QuadtreeElement<const char*>* entry = list->get(idx);

    //printf("\n[%d]: %d", idx, entry->value);
    printf("\n[%d]: (%d, %d): %s", idx, entry->horzPos, entry->vertPos, entry->value);
  }

  printf("\n");
}
