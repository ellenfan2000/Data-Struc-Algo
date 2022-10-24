#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

void fillaBlank(char * line) {
  int oldLength = strlen(line);
  char * firstSep = strchr(line, '_');
  char * nextSep;
  //char * category = NULL;
  if ((nextSep = strchr(firstSep + 1, '_')) == NULL) {
    fprintf(stderr, "%s\n", "wrong input");
    exit(EXIT_FAILURE);
  }

  //get category
  int len = nextSep - firstSep;
  char category[len];
  strncpy(category, firstSep + 1, len - 1);

  firstSep[0] = '\0';
  nextSep++;
  const char * word = chooseWord(category, NULL);

  char laststr[strlen(nextSep)];
  strcpy(laststr, nextSep);
  int newLength = oldLength - strlen(category) - 2 + strlen(word);
  line = realloc(line, newLength * sizeof(*line));
  strcat(line, word);
  strcat(line, nextSep);
}

void parseLine(char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("could not open file.");
  }
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    //find the space and the corresponding category
    if (strchr(line, '_') == NULL) {
      continue;
    }
    while (strchr(line, '_') != NULL) {
      fillaBlank(line);
    }
    //print
    printf("%s", line);
  }
}

void freeAll() {
}
