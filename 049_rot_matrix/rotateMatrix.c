#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINESIZE 12
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int matrix[LINESIZE][LINESIZE];
  char line[LINESIZE + 2];
  int inputSize = 0;

  while (fgets(line, LINESIZE + 2, f) != NULL) {
    if (inputSize > 9) {
      printf("Too mush rows!");
      return EXIT_FAILURE;
    }
    if (strchr(line, '\n') == NULL) {
      printf("line is too long");
      return EXIT_FAILURE;
    }
    for (int j = 0; j < 10; j++) {
      matrix[j][10 - inputSize - 1] = line[j];
    }
    inputSize++;
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }

  return EXIT_SUCCESS;
}
