#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  int size = 0;
  counts_t * c = malloc(1 * sizeof(*c));
  c->counts = malloc(1 * sizeof(*(c->counts)));
  c->size = size;
  c->unknown_count = 0;
  return c;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  int in_c = 0;
  if (!name) {
    c->unknown_count++;
  }
  else {
    for (int i = 0; i < c->size; i++) {
      if (!strcmp(name, c->counts[i].str)) {
        c->counts[i].times++;
        in_c = 1;
      }
    }
    if (in_c == 0) {
      c->size++;
      c->counts = realloc(c->counts, c->size * sizeof(*(c->counts)));
      one_count_t oc;
      oc.str = name;
      oc.times = 1;
      c->counts[c->size - 1] = oc;
    }
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->size; i++) {
    fprintf(outFile, "%s: %d\n", c->counts[i].str, c->counts[i].times);
  }
  if (c->unknown_count > 0) {
    fprintf(outFile, "%s: %d\n", "<unknown>", c->unknown_count);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  free(c->counts);
  free(c);
}
