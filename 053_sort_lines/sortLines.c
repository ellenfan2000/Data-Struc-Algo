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

size_t parseLine(char ** data, FILE * stream) {
  char * line = NULL;
  size_t sz = 0;
  size_t count = 0;
  while (getline(&line, &sz, stream) >= 0) {
    count++;
    data = realloc(data, count * sizeof(*data));
    data[count - 1] = line;
    line = NULL;
  }
  free(line);
  return count;
}
int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  char * line = NULL;
  size_t sz = 0;
  size_t count = 0;
  char ** data = NULL;
  if (argc == 1) {
    while (getline(&line, &sz, stdin) >= 0) {
      count++;
      data = realloc(data, count * sizeof(*data));
      data[count - 1] = line;
      line = NULL;
    }
    //count = parseLine(data, stdin);
    sortData(data, count);
  }
  else {
    for (int i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        perror("Could Not Open File");
        return EXIT_FAILURE;
      }
      while (getline(&line, &sz, f) >= 0) {
        count++;
        data = realloc(data, count * sizeof(*data));
        data[count - 1] = line;
        line = NULL;
      }
      if (fclose(f) != 0) {
        perror("failed to close input file");
        return EXIT_FAILURE;
      }
    }
    sortData(data, count);
  }
  free(line);
  for (size_t i = 0; i < count; i++) {
    printf("%s", data[i]);
    free(data[i]);
  }
  free(data);
  return EXIT_SUCCESS;
}
