#include <stdio.h>
#include <stdlib.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "usage:");
    return EXIT_FAILURE;
  }
  parseStoryLine(argv[1], NULL, 0, 1);
  return EXIT_SUCCESS;
}
