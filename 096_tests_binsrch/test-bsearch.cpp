#include <cmath>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);
class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};
class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class LinearFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 100 * arg + 98; }
};

class number : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg - 100; }
};

class QuadFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg * arg - 100; }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int maxInvo;
  if (high > low) {
    maxInvo = log2(high - low) + 1;
  }
  else {
    maxInvo = 1;
  }

  CountedIntFn func(maxInvo, f, mesg);
  int ans = binarySearchForZero(&func, low, high);
  //std::cout << ans << std::endl;
  if (ans != expected_ans) {
    fprintf(stderr, "Wrong Invocation %s \n", mesg);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  LinearFunction func;
  check(&func, 10, 30, 10, "LF all positive");
  check(&func, -1, 4, -1, "LF: at low");
  check(&func, -1, -1, -1, "LF: low = high = answer");
  check(&func, -100000, -100, -101, "LF: All negative");
  check(&func, 10, 10, 10, "LF: low=high != answer");
  check(&func, -100000, 100000, -1, "LF: ");
  check(&func, -100000, -1, -2, "LF: ");

  SinFunction f;
  check(&f, 0, 150000, 52359, "Sin Function");

  number f1;
  check(&f1, 0, 100, 99, "num");

  QuadFunction f2;
  check(&f2, 0, 20, 10, "Quad");
  check(&f2, 0, 10, 9, "Quad");
  check(&f2, 0, 10000, 10, "Quad");
  check(&f2, 0, 1000000, 458752, "Quad");
  check(&f2, 9, 10, 9, "Quad");
  check(&f2, 10, 10000, 10, "Quad");

  return EXIT_SUCCESS;
}
