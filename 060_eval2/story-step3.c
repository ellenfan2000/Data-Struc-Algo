#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc < 3) {
    fprintf(stderr, "usage:program words_file story files");
    return EXIT_FAILURE;
  }
  catarray_t * arr = readCatArr(argv[1]);
  parseStoryLine(argv[2], arr, 0);
  freeCatArray(arr);
  return EXIT_SUCCESS;
}
