#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  size_t length = 1;
  size_t max = 0;
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return length;
  }
  for (size_t i = 1; i < n; i++) {
    if (array[i] > array[i - 1]) {
      length++;
      if (i == n - 1 && length > max) {
        max = length;
      }
    }
    else {
      if (length > max) {
        max = length;
      }
      length = 1;
    }
  }
  return max;
}
