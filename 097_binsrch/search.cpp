#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low == high || f->invoke(low) > 0) {
    return low;
  }
  else if (f->invoke(high) < 0) {
    return high - 1;
  }
  else {
    int mid = (high + low) / 2;

    if (f->invoke(mid) > 0) {
      return binarySearchForZero(f, low, mid);
    }
    else if (f->invoke(mid) == 0) {
      return mid;
    }
    else {
      return binarySearchForZero(f, mid, high);
    }
  }
}
