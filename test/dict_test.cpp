
#include <time.h>
#include <stdio.h>
#include <cstddef>

//#include "../lib/core/dict.hpp"
#include "../lib/core/dict/hash_map.hpp"
#include "../lib/core/dict/tree_map.hpp"
#include "../lib/core/list.hpp"

int main() {

  //Dict<const char*>* dict = new Dict<const char*>();
  //HashMap<const char*>* dict = new HashMap<const char*>();
  TreeMap<const char*>* dict = new TreeMap<const char*>();

  printf("\n====================================================");

  //if (dict->get("a-nonexistent-key") == NULL) {
  //  printf("\n[%ld] null: %p", time(NULL), dict->get("a-nonexistent-key"));
  //}

  dict->set("crap", "crap!");
  dict->set("shit", "shit!");
  dict->set("poot", "poot!");
  dict->set("poop", "poop!");
  dict->set("crappity", "crappity!");
  dict->set("assy", "assy!");
  dict->set("one", "one!");
  dict->set("two", "two!");
  dict->set("three", "three!");
  dict->set("four", "four!");
  dict->set("five", "five!");

  dict->set("crap", "crap!!");
  dict->set("shit", "shit!!");
  dict->set("poot", "poot!!");
  dict->set("poop", "poop!!");
  dict->set("crappity", "crappity!!");
  dict->set("assy", "assy!!");
  dict->set("one", "one!!");
  dict->set("two", "two!!");
  dict->set("three", "three!!");
  dict->set("four", "four!!");
  dict->set("five", "five!!");

  dict->set("AAAA", "aaaa");
  dict->set("BBBB", "bbbb");
  dict->set("CCCC", "cccc");
  dict->set("DDDD", "dddd");
  dict->set("EEEE", "eeee");
  dict->set("FFFF", "ffff");
  dict->set("GGGG", "gggg");
  dict->set("HHHH", "hhhh");

  printf("\n");

  //dict->rebase(512);


  for (uint32_t listIdx = 0; listIdx < 32767 * 2; listIdx++) {
    char* str = (char*)malloc(32);

    sprintf(str, "%d", listIdx);

    dict->set(str, str);
  }


  printf("\n[%ld] crap: %s", time(NULL), dict->get("crap"));
  printf("\n[%ld] shit: %s", time(NULL), dict->get("shit"));
  printf("\n[%ld] poot: %s", time(NULL), dict->get("poot"));
  printf("\n[%ld] poop: %s", time(NULL), dict->get("poop"));
  printf("\n[%ld] crappity: %s", time(NULL), dict->get("crappity"));
  printf("\n[%ld] assy: %s", time(NULL), dict->get("assy"));

  printf("\n[%ld] one: %s", time(NULL), dict->get("one"));
  printf("\n[%ld] two: %s", time(NULL), dict->get("two"));
  printf("\n[%ld] three: %s", time(NULL), dict->get("three"));
  printf("\n[%ld] four: %s", time(NULL), dict->get("four"));
  printf("\n[%ld] five: %s", time(NULL), dict->get("five"));

  printf("\n\n");

  List<const char*>* keys = dict->getKeys();
  List<const char*>* vals = dict->getValues();

  for (int idx = 0; idx < keys->getLength(); idx++) {
    printf("%s => %s\n", keys->get(idx), vals->get(idx));
  }

  printf("\n%d\n", keys->getLength());

  printf("\n");

  printf("\n====================================================\n\n");


  delete keys;
  delete vals;
  delete dict;
}
