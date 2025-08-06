
#include <time.h>
#include <stdio.h>
#include <cstddef>

#include <core/map/hash_map.hpp>
#include <core/map/tree_map.hpp>
//#include <core/list/list.hpp>


int32_t cmpFunc(const char* left, const char* right) {
  return 1;
}


int main() {

  //Dict<const char*>* map = new Dict<const char*>();
  HashMap<const char*>* map = new HashMap<const char*>();
  //TreeMap<const char*>* map = new TreeMap<const char*>();

  printf("\n====================================================");

  //if (map->get("a-nonexistent-key") == NULL) {
  //  printf("\n[%ld] null: %p", time(NULL), map->get("a-nonexistent-key"));
  //}

//  map->set("crap", "crap!");
//  map->set("shit", "shit!");
//  map->set("poot", "poot!");
//  map->set("poop", "poop!");
//  map->set("crappity", "crappity!");
//  map->set("assy", "assy!");
//  map->set("one", "one!");
//  map->set("two", "two!");
//  map->set("three", "three!");
//  map->set("four", "four!");
//  map->set("five", "five!");
//
//  map->set("crap", "crap!!");
//  map->set("shit", "shit!!");
//  map->set("poot", "poot!!");
//  map->set("poop", "poop!!");
//  map->set("crappity", "crappity!!");
//  map->set("assy", "assy!!");
//  map->set("one", "one!!");
//  map->set("two", "two!!");
//  map->set("three", "three!!");
//  map->set("four", "four!!");
//  map->set("five", "five!!");
//
//  map->set("AAAA", "aaaa");
//  map->set("BBBB", "bbbb");
//  map->set("CCCC", "cccc");
//  map->set("DDDD", "dddd");
//  map->set("EEEE", "eeee");
//  map->set("FFFF", "ffff");
//  map->set("GGGG", "gggg");
//  map->set("HHHH", "hhhh");

  printf("\n");

  //map->rebase(512);


  for (uint32_t listIdx = 0; listIdx < 8192; listIdx++) {
    char* str = (char*)malloc(32);

    sprintf(str, "%d", listIdx);

    if ((listIdx % 512) == 0) {
      printf(".");
      fflush(stdout);
    }

    map->set(str, str);
  }


//  printf("\n[%ld] crap: %s", time(NULL), map->get("crap"));
//  printf("\n[%ld] shit: %s", time(NULL), map->get("shit"));
//  printf("\n[%ld] poot: %s", time(NULL), map->get("poot"));
//  printf("\n[%ld] poop: %s", time(NULL), map->get("poop"));
//  printf("\n[%ld] crappity: %s", time(NULL), map->get("crappity"));
//  printf("\n[%ld] assy: %s", time(NULL), map->get("assy"));
//
//  printf("\n[%ld] one: %s", time(NULL), map->get("one"));
//  printf("\n[%ld] two: %s", time(NULL), map->get("two"));
//  printf("\n[%ld] three: %s", time(NULL), map->get("three"));
//  printf("\n[%ld] four: %s", time(NULL), map->get("four"));
//  printf("\n[%ld] five: %s", time(NULL), map->get("five"));

  printf("\n\n");

  LinkedList<const char*>* keys = map->getKeys(cmpFunc);
  LinkedList<const char*>* vals = map->getValues(cmpFunc);

  for (int idx = 0; idx < keys->getLength(); idx++) {
    const char* key = keys->get(idx);
    //const char* val = vals->get(idx);
    const char* val = map->get(key);

    printf("%s => %s\n", key, val);

    //free((void*)key);
    //free((void*)val);
  }

  //printf("\n%d\n", keys->getLength());

  printf("\n");

  printf("\n====================================================\n\n");


  //delete keys;
  //delete vals;
  //delete map;
}
