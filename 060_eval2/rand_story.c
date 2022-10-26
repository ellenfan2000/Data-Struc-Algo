#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

/*
char * line: read from file
catarray_t * arr: category array read from words.txt
category_t * pw: stores the previously used words
int arg: whether has -n then running the function, 1 for yes, 0 for no
This function take case of one blank each time. It locates the blank and
fills the blank with words chosen.
*/
char * fillaBlank(char * line, catarray_t * arr, category_t * pw, int arg) {
  //find the _
  char * firstSep = strchr(line, '_');
  char * nextSep;

  //if the line only has one _ without the pair _. exit
  if ((nextSep = strchr(firstSep + 1, '_')) == NULL) {
    fprintf(stderr, "%s\n", "wrong input");
    exit(EXIT_FAILURE);
  }

  //get category
  int blank_len = nextSep - firstSep;
  char category[blank_len];
  strncpy(category, firstSep + 1, blank_len - 1);
  category[blank_len - 1] = '\0';

  //get word
  char * word;
  char * endstr = NULL;
  long num = strtol(category, &endstr, 10);

  //if category is not a pure numebr
  if (endstr[0] != '\0' || blank_len == 1 || num == 0) {
    const char * word_con = chooseWord(category, arr);
    word = strdup(word_con);
    if (arg == 1) {
      removeWord(arr, lookupCategory(arr, category), word);
    }
  }
  else {
    word = getPrevious(pw, num);
  }
  addWord(pw, word);

  //print out result
  *firstSep = '\0';
  nextSep++;
  printf("%s%s", line, word);
  line = nextSep;
  return line;
}

/*
char * fname: file name of the story
catarray_t * arr: categories read from words.txt
int arg: whether -n is used, 1 for yes, 0 for no
This function reads lines from story, for each blank, call fillablank 
to fill blanks in the line and print the filled line. 
*/
void parseStoryLine(char * fname, catarray_t * arr, int arg) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    freeCatArray(arr);
    fprintf(stderr, "Could not open file: %s.\n", fname);
    exit(EXIT_FAILURE);
  }

  //initial a category_t to store all the used words.
  category_t * pw = initialCate("previous");
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    // if the line does not have blank, go the the next line
    if (strchr(line, '_') == NULL) {
      continue;
    }
    char * ptr = line;
    while (strchr(ptr, '_') != NULL) {
      ptr = fillaBlank(ptr, arr, pw, arg);
    }
    printf("%s", ptr);
  }

  free(line);
  if (fclose(f) != 0) {
    perror("Cannot close file\n");
    exit(EXIT_FAILURE);
  }
  freePW(pw);
}

/*
category_t * pw: stores all used words
this function frees all the alocated memory for
previous used words.
*/
void freePW(category_t * pw) {
  for (size_t i = 0; i < pw->n_words; i++) {
    free(pw->words[i]);
  }
  free(pw->words);
  free(pw);
}

/*
char * fname: the file name for the words need to read
This function returns a catarray_t to store all the
category:words pairs.
*/
catarray_t * readCatArr(const char * fname) {
  //initialize and malloc catarray
  catarray_t * catarr = malloc(sizeof(*catarr));
  catarr->n = 0;
  catarr->arr = malloc(sizeof(*(catarr->arr)));

  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open file: %s", fname);
    exit(EXIT_FAILURE);
  }

  char * line = NULL;
  char * line_dup = NULL;
  char * name;
  char * word;
  size_t sz = 0;

  //index of the category want to find in catarr->arr
  int ind;

  while (getline(&line, &sz, f) >= 0) {
    if (strchr(line, ':') == NULL) {
      perror("Invalid Line");
      exit(EXIT_FAILURE);
    }

    //seperate the line to get name and word.
    line_dup = line;
    name = strdup(strsep(&line_dup, ":"));
    word = strdup(strsep(&line_dup, "\n"));

    //if the category in not in catarr->arr
    if ((ind = lookupCategory(catarr, name)) == -1) {
      category_t * category = initialCate(name);
      addWord(category, word);
      catarr->n++;
      catarr->arr = realloc(catarr->arr, catarr->n * sizeof(*(catarr->arr)));
      catarr->arr[catarr->n - 1] = *category;
      free(category);
    }
    else {  //if the category is in catarr->arr
      free(name);
      addWord(&catarr->arr[ind], word);
    }
  }
  if (fclose(f) != 0) {
    perror("Could not close file!");
    exit(EXIT_FAILURE);
  }
  free(line);
  return catarr;
}

/*
catarray_t * arr: array stors all the categories
const char * name: name of one category
This function returns the index of the category specified by
name in arr->arr. If the category is not in the arr, return -1. 
*/
int lookupCategory(catarray_t * arr, const char * name) {
  for (size_t i = 0; i < arr->n; i++) {
    if (!strcmp(arr->arr[i].name, name)) {
      return i;
    }
  }
  return -1;
}

/*
free all the allocated memory for arr
*/
void freeCatArray(catarray_t * arr) {
  for (size_t i = 0; i < arr->n; i++) {
    for (size_t j = 0; j < arr->arr[i].n_words; j++) {
      free(arr->arr[i].words[j]);
    }
    free(arr->arr[i].name);
    free(arr->arr[i].words);
  }
  free(arr->arr);
  free(arr);
}

/*
initial a category_t struct specifing the category name
*/
category_t * initialCate(char * name) {
  category_t * pw = malloc(sizeof(*pw));
  pw->name = name;
  pw->words = malloc(sizeof(*(pw->words)));
  pw->n_words = 0;
  return pw;
}

/*
category_t * cate: category
char * word: word to be added into the category
This function adds a word into the sepecific category
*/
void addWord(category_t * cate, char * word) {
  cate->n_words++;
  cate->words = realloc(cate->words, cate->n_words * sizeof(*(cate->words)));
  cate->words[cate->n_words - 1] = word;
}

/*
category_t * pw:
size_t num: 
The function returns the numth previously used word. If num
is larger than the number of words stored in pw, return Null. 
*/
char * getPrevious(category_t * pw, size_t num) {
  if (num > pw->n_words) {
    fprintf(stderr, "no enought words for Backreference number:%lu\n ", num);
    exit(EXIT_FAILURE);
  }
  char * ans = strdup(pw->words[pw->n_words - num]);
  return ans;
}
/*
remove a word of a category stored in a catarray_t and free memory
of that word
*/
void removeWord(catarray_t * arr, size_t ind, char * word) {
  size_t newsize = arr->arr[ind].n_words - 1;
  arr->arr[ind].n_words--;
  char ** temp = malloc(newsize * sizeof(*temp));
  size_t i = 0;
  size_t j = 0;

  while (j < newsize + 1) {
    if (!strcmp(arr->arr[ind].words[j], word)) {
      free(arr->arr[ind].words[j]);
      j++;
      continue;
    }
    else {
      temp[i] = arr->arr[ind].words[j];
      i++;
      j++;
    }
  }
  free(arr->arr[ind].words);
  arr->arr[ind].words = temp;
}
