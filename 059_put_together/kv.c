#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  kvarray_t * kvarray = malloc(sizeof(*kvarray));
  int count = 0;

  //kvarray->length = 0;
  kvarray->pairs = malloc(sizeof(*(kvarray->pairs)));

  // kvpair_t * pair = malloc(sizeof(*pair));
  kvpair_t pair;
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("No such file");
    exit(EXIT_FAILURE);
  }

  char * line = NULL;
  char * line_cp;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    count++;

    if (strchr(line, '=') == NULL) {
      perror("Invalid Line");
      exit(EXIT_FAILURE);
    }

    line_cp = strdup(line);
    // pair->key = strsep(&line_cp, "=");
    // pair->value = line_cp;
    // pair->value = strsep(&line_cp, "\n");
    pair.key = strsep(&line_cp, "=");
    pair.value = strsep(&line_cp, "\n");
    kvarray->pairs = realloc(kvarray->pairs, count * sizeof(*(kvarray->pairs)));
    kvarray->pairs[count - 1] = pair;
  }
  fclose(f);
  kvarray->length = count;
  free(line);
  return kvarray;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  int len = pairs->length;
  for (int i = 0; i < len; i++) {
    free(pairs->pairs[i].key);
  }
  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  int len = pairs->length;
  for (int i = 0; i < len; i++) {
    printf("key = '%s' value = '%s'\n", (pairs->pairs[i]).key, (pairs->pairs[i]).value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  int len = pairs->length;
  for (int i = 0; i < len; i++) {
    if (!strcmp(pairs->pairs[i].key, key)) {
      return (pairs->pairs[i]).value;
    }
  }
  return NULL;
}
