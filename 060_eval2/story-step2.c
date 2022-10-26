#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "usage:program story.txt");
    return EXIT_FAILURE;
  }
  catarray_t * a = readCatArr(argv[1]);
  printWords(a);
  freeCatArray(a);
  return EXIT_SUCCESS;
}
