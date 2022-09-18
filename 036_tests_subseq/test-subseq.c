#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void) {
  size_t n1 = 8;
  int array1[8] = {
      1, 2, 3, 1, 2, 3, 4, 5};  //may only consider the first consequtive sequence
  size_t n2 = 10;
  int array2[10] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};  //consecutive
  size_t n3 = 6;
  int array3[6] = {1, 2, 2, 3, 4, 5};  //wrongly use >= and >
  size_t n4 = 5;
  int array4[] = {1, 1, 1, 1, 1};
  size_t n5 = 7;
  int array5[] = {1, 2, 3, 1, 2, 3, 4};  //omit last number
  size_t n6 = 6;
  int array6[] = {-1, 1, 3, 5, 7, 2, 3};

  size_t ans = 5;

  if (maxSeq(array1, n1) != ans) {
    printf("test case1, expect %lu, get %lu \n", ans, maxSeq(array1, n1));
    return EXIT_FAILURE;
  }

  ans = 4;
  if (maxSeq(array2, n2) != ans) {
    printf("test case2,expect %lu, get %lu \n", ans, maxSeq(array2, n2));
    return EXIT_FAILURE;
  }

  if (maxSeq(array3, n3) != ans) {
    printf("test case3,expect %lu, get %lu \n", ans, maxSeq(array3, n3));
    return EXIT_FAILURE;
  }

  ans = 1;
  if (maxSeq(array4, n4) != ans) {
    printf("test case4,expect %lu, get %lu \n", ans, maxSeq(array4, n4));
    return EXIT_FAILURE;
  }

  ans = 4;
  if (maxSeq(array5, n5) != ans) {
    printf("test case5,expect %lu, get %lu \n", ans, maxSeq(array5, n5));
    return EXIT_FAILURE;
  }

  ans = 0;
  if (maxSeq(NULL, 0) != ans) {
    printf("test case 7, expect %lu, get %lu \n", ans, maxSeq(NULL, 0));
    return EXIT_FAILURE;
  }

  ans = 5;
  if (maxSeq(array6, n6) != ans) {
    printf("test case6,expect %lu, get %lu \n", ans, maxSeq(array6, n6));
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
