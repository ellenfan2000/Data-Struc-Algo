#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use
struct previousCollect_tag {
  char ** words;
  size_t n;
};
typedef struct previousCollect_tag previousCollect_t;

char * fillaBlank(char * line, catarray_t * arr, category_t * pw, int arg);
void parseStoryLine(char * fname, catarray_t * arr, int arg);
void freePW(category_t * pw);
catarray_t * readCatArr(const char * fname);
int lookupCategory(catarray_t * arr, const char * name);
void freeCatArray(catarray_t * arr);
category_t * initialCate(char * name);
void addWord(category_t * pw, char * word);
//char * randomChoose(catarray_t * arr, char * category);
char * getPrevious(category_t * pw, size_t num);
void removeWord(catarray_t * arr, size_t ind, char * word);
#endif
