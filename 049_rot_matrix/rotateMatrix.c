#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINESIZE 10

void rotate(FILE * f, char matrix[][LINESIZE]) {
  int inputSize = 0;
  char line[LINESIZE + 2];
  while (fgets(line, LINESIZE + 2, f) != NULL) {
    if (inputSize > 9) {
      // fclose(f);
      perror("Too mush rows!\n");
      exit(EXIT_FAILURE);
    }
    if (strchr(line, '\n') == NULL) {
      // fclose(f);
      perror("line is too long! \n");
      exit(EXIT_FAILURE);
    }
    if (line[10] != '\n') {
      //fclose(f);
      perror("line is too short!\n");
      exit(EXIT_FAILURE);
    }
    for (int j = 0; j < LINESIZE; j++) {
      matrix[j][10 - inputSize - 1] = line[j];
    }
    inputSize++;
  }
  if (inputSize < 9) {
    //fclose(f);
    perror("Too Less lines\n");
    exit(EXIT_FAILURE);
  }

  if (fclose(f) != 0) {
    perror("failed to close file\n");
    exit(EXIT_FAILURE);
  }
}
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file\n");
    return EXIT_FAILURE;
  }

  char matrix[LINESIZE][LINESIZE];
  rotate(f, matrix);
  /* char line[LINESIZE + 2]; */
  /* int inputSize = 0; */

  /* while (fgets(line, LINESIZE + 2, f) != NULL) { */
  /*   if (inputSize > 9) { */
  /*     // fclose(f); */
  /*     perror("Too mush rows!\n"); */
  /*     return EXIT_FAILURE; */
  /*   } */
  /*   if (strchr(line, '\n') == NULL) { */
  /*     // fclose(f); */
  /*     perror("line is too long! \n"); */
  /*     return EXIT_FAILURE; */
  /*   } */
  /*   if (line[10] != '\n') { */
  /*     //fclose(f); */
  /*     perror("line is too short!\n"); */
  /*     return EXIT_FAILURE; */
  /*   } */
  /*   for (int j = 0; j < LINESIZE; j++) { */
  /*     matrix[j][10 - inputSize - 1] = line[j]; */
  /*   } */
  /*   inputSize++; */
  /* } */
  /* if (inputSize < 9) { */
  /*   //fclose(f); */
  /*   perror("Too Less lines\n"); */
  /*   return EXIT_FAILURE; */
  /* } */

  /* if (fclose(f) != 0) { */
  /*   perror("failed to close file\n"); */
  /*   return EXIT_FAILURE; */
  /* } */
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }

  return EXIT_SUCCESS;
}
