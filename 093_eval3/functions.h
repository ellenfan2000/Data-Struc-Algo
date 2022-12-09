#include <climits>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "exception.h"

/*
str: string that going to convert to number
idx: the first character in string after number
*/
long myStrtol(std::string str, size_t * idx = 0, int base = 10) {
  const char * string = str.c_str();
  char * endptr;
  long ans = strtol(string, &endptr, base);
  if (idx) {
    *idx = endptr - string;
  }

  /*whether the string is converted:
  1. non-digit chars before numbers
  2. empty str
  */
  if (ans == 0) {
    size_t pos = 0;
    //overlook all whitespace characters
    while (isspace(str[pos])) {
      pos++;
    }
    if (!isdigit(str[pos])) {
      throw InvalidNumber(str);
    }
  }
  return ans;
}

unsigned long myStrtoul(std::string str, size_t * idx = 0, int base = 10) {
  const char * string = str.c_str();
  char * endptr;

  //test if it is a negative number
  long ans1 = strtol(string, &endptr, base);
  if (ans1 < 0) {
    throw InvalidNumber(str);
  }
  unsigned long ans = strtoul(string, &endptr, base);
  if (idx) {
    *idx = endptr - string;
  }

  /*whether the string is converted:
  1. non-digit chars before numbers
  2. empty str
  */
  if (ans == 0) {
    size_t pos = 0;
    //overlook all whitespace characters
    while (isspace(str[pos])) {
      pos++;
    }
    if (!isdigit(str[pos])) {
      throw InvalidNumber(str);
    }
  }

  return ans;
}
