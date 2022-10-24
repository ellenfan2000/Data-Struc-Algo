#include <stdio.h>
#include <stdlib.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc < 2) {
    fprintf(stderr, "usage:");
  }
  parseLine(argv[1]);
}
