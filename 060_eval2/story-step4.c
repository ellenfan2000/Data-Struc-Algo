#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc < 3 || argc > 4) {
    fprintf(stderr, "usage:program option[-n] words_file story files\n");
    return EXIT_FAILURE;
  }
  char * word_file;
  char * story_file;
  int arg;
  if (argc == 3) {
    word_file = argv[1];
    story_file = argv[2];
    arg = 0;
  }
  if (argc == 4 && !strcmp(argv[1], "-n")) {
    word_file = argv[2];
    story_file = argv[3];
    arg = 1;
  }

  if (argc == 4 && strcmp(argv[1], "-n")) {
    fprintf(stderr, "Usage:program option[-n] words_file story files\n");
    return EXIT_FAILURE;
  }
  catarray_t * arr = readCatArr(word_file);
  parseStoryLine(story_file, arr, arg);
  freeCatArray(arr);
  return EXIT_SUCCESS;
}
