#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int arrayMax(int * array, int n) {
  if (n > 0) {
    int largest_index = 0;
    for (int i = 0; i < n; i++) {
      if (array[i] > array[largest_index]) {
        largest_index = i;
      }
    }
    int c = 'a' + largest_index;
    return c;
  }
  return 0;
}

int * frequencyCount(int * freq, FILE * f) {
  int c;
  int i;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      i = c - 'a';
      freq[i] += 1;
    }
  }
  return freq;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int freq[26] = {0};
  frequencyCount(freq, f);
  int c = arrayMax(freq, 26);
  int key = c - 'e';
  printf("%d\n", key);
  return EXIT_SUCCESS;
  //int key = decrypt(ma);
}
