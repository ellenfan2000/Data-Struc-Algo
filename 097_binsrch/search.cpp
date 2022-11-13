#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low == high || low == high - 1) {
    return low;
  }
  else {
    int mid = (high + low) / 2;
    int val = f->invoke(mid);
    if (val > 0) {
      return binarySearchForZero(f, low, mid);
    }
    else if (val == 0) {
      return mid;
    }
    else {
      return binarySearchForZero(f, mid, high);
    }
  }
}
