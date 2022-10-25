#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc < 3) {
    fprintf(stderr, "usage:program option[-n] words_file story files");
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
  else {
    word_file = argv[2];
    story_file = argv[3];
    arg = 1;
  }
  catarray_t * arr = readCatArr(word_file);
  //printWords(arr);
  parseStoryLine(story_file, arr, arg);
  printWords(arr);
  freeCatArray(arr);
  return EXIT_SUCCESS;
}
