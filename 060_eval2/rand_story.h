#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use
void fillaBlank(char * line);
void parseStoryLine(char * fname);
void free();
catarray_t * readCatArr(const char * fname);
int lookupCategory(catarray_t * arr, const char * name);
void freeCatArray(catarray_t * arr);
#endif
