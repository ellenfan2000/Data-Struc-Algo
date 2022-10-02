#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

char ** parseLine(char ** data, FILE * stream, size_t * count) {
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, stream) >= 0) {
    *count = *count + 1;
    data = realloc(data, *count * sizeof(*data));
    data[*count - 1] = line;
    line = NULL;
  }
  free(line);
  return data;
}

void free_all(char ** data, size_t count) {
  //free(line);
  for (size_t i = 0; i < count; i++) {
    printf("%s", data[i]);
    free(data[i]);
  }
  free(data);
}
int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  size_t count = 0;
  char ** data = NULL;
  if (argc == 1) {
    data = parseLine(data, stdin, &count);
    sortData(data, count);
  }
  else {
    for (int i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        perror("Could Not Open File");
        free_all(data, count);
        return EXIT_FAILURE;
      }
      data = parseLine(data, f, &count);
      sortData(data, count);
      free_all(data, count);
      data = NULL;
      count = 0;
      if (fclose(f) != 0) {
        perror("failed to close input file");
        free_all(data, count);
        return EXIT_FAILURE;
      }
    }
    //sortData(data, count);
  }
  // free_all(data, count);
  return EXIT_SUCCESS;
}
