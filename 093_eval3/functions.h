#include <climits>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "exception.h"
long my_strtol(std::string str, size_t * idx = 0, int base = 10) {
  const char * string = str.c_str();
  char * endptr;
  long ans = strtol(string, &endptr, base);
  if (idx) {
    *idx = endptr - string;
  }
  if (ans == 0) {
    size_t pos = 0;
    while (str[pos] == ' ') {
      pos++;
    }
    if (!isdigit(str[pos])) {
      throw InvalidLine(str);
    }
  }
  return ans;
}

unsigned long my_strtoul(std::string str, size_t * idx = 0, int base = 10) {
  const char * string = str.c_str();
  char * endptr;
  unsigned long ans = strtoul(string, &endptr, base);
  if (idx) {
    *idx = endptr - string;
  }
  if (ans == 0) {
    size_t pos = 0;
    while (str[pos] == ' ') {
      pos++;
    }
    if (!isdigit(str[pos])) {
      throw InvalidLine(str);
    }
  }

  return ans;
}
