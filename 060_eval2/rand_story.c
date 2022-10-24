#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

void fillaBlank(char * line) {
  int oldLength = strlen(line) + 1;

  char * firstSep = strchr(line, '_');
  char * nextSep;
  //char * category = NULL;
  if ((nextSep = strchr(firstSep + 1, '_')) == NULL) {
    fprintf(stderr, "%s\n", "wrong input");
    exit(EXIT_FAILURE);
  }
  //get category
  int blank_len = nextSep - firstSep;
  char category[blank_len];
  strncpy(category, firstSep + 1, blank_len - 1);

  firstSep[0] = '\0';
  nextSep++;
  const char * word = chooseWord(category, NULL);

  char laststr[strlen(nextSep) + 1];
  strcpy(laststr, nextSep);
  int newLength = oldLength - blank_len - 1 + strlen(word);

  if (newLength > oldLength) {
    line = realloc(line, newLength * sizeof(*line));
  }
  strcat(line, word);
  strcat(line, laststr);
}

void parseStoryLine(char * fname) {
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
    // char * line_dup = strdup(line);
    while (strchr(line, '_') != NULL) {
      fillaBlank(line);
    }
    //print
    printf("%s", line);
  }
  free(line);
  if (fclose(f) != 0) {
    perror("cannot close file");
    exit(EXIT_FAILURE);
  }
}

void freeAll() {
}

catarray_t * readCatArr(const char * fname) {
  catarray_t * catarr = malloc(sizeof(*catarr));
  catarr->n = 0;
  catarr->arr = malloc(sizeof(*(catarr->arr)));

  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("No such file");
    exit(EXIT_FAILURE);
  }

  char * line = NULL;
  char * line_dup = NULL;
  char * name;
  size_t sz = 0;
  int ind;
  while (getline(&line, &sz, f) >= 0) {
    if (strchr(line, ':') == NULL) {
      perror("Invalid Line");
      exit(EXIT_FAILURE);
    }
    line_dup = strdup(line);
    // token = line_dup;
    name = strsep(&line_dup, ":");

    if ((ind = lookupCategory(catarr, name)) == -1) {
      category_t category;
      category.n_words = 1;
      category.words = malloc(sizeof(*(category.words)));
      category.name = name;
      category.words[0] = strsep(&line_dup, "\n");

      catarr->n++;
      catarr->arr = realloc(catarr->arr, catarr->n * sizeof(*(catarr->arr)));
      catarr->arr[catarr->n - 1] = category;
    }
    else {
      catarr->arr[ind].n_words++;
      catarr->arr[ind].words =
          realloc(catarr->arr[ind].words,
                  catarr->arr[ind].n_words * sizeof(*(catarr->arr[ind].words)));

      catarr->arr[ind].words[catarr->arr[ind].n_words - 1] = strsep(&line_dup, "\n");
    }
  }
  fclose(f);
  free(line);

  return catarr;
}

int lookupCategory(catarray_t * arr, const char * name) {
  for (size_t i = 0; i < arr->n; i++) {
    if (!strcmp(arr->arr[i].name, name)) {
      return i;
    }
  }
  return -1;
}

void freeCatArray(catarray_t * arr) {
  for (size_t i = 0; i < arr->n; i++) {
    for (size_t j = 0; j < arr->arr[i].n_words; i++) {
      free(arr->arr[i].words[j]);
    }
    free(arr->arr[i].words);
  }
  free(arr->arr);
  free(arr);
}
