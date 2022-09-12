#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans) {
    printf("For input %d,%d, expected answer is %d, power answer is %d\n",
           x,
           y,

           expected_ans,
           power(x, y));
    // printf("Wrong answer! \n");
    exit(EXIT_FAILURE);
  }
}
int main(void) {
  run_check(0, 0, 1);
  run_check(10, 0, 1);
  run_check(10, 1, 10);
  run_check(2, 6, 64);
  run_check(1, 10, 1);
  run_check(-3, 2, 9);
  run_check(-3, 3, -27);

  return EXIT_SUCCESS;
}
