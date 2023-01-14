#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  uint64_t * ans = new uint64_t[257]();
  int c;
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    std::cerr << "Invalid file!" << std::endl;
    exit(EXIT_FAILURE);
  }
  while ((c = fgetc(f)) != EOF) {
    ans[c]++;
  }
  ans[256] = 1;
  fclose(f);
  return ans;
}
