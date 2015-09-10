#Include <stdio.h>
#include <ctype.h>

struct varor {
  char namn[50];
  int pris;
  char beskrivning[50];
  char location[50];
};

void vara_add(struct varor *vara);

int main() {
  struct varor vara1 = 
    (struct varor) {.namn="b", .pris=0, .beskrivning="", .location=""};

  vara_add(&vara1);
  printf("%s\n", vara1.namn);
  return 0;
}

void vara_add(struct varor *vara) {
  printf("Namn: \n");
  scanf("%s", vara->namn);
}
