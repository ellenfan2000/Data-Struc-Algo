#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "bstset.h"
#include "set.h"

int main(void) {
  BstSet<int> s1;
  s1.add(10);
  s1.add(20);
  s1.add(30);
  s1.add(15);
  s1.add(24);
  s1.add(1);
  s1.add(0);

  std::cout << "current set is:" << std::endl;
  s1.print();
  std::cout << std::endl;

  s1.remove(10);
  s1.remove(20);
  s1.remove(24);
  std::cout << "then set becomes:" << std::endl;
  s1.print();
  std::cout << std::endl;

  if (!s1.contains(24)) {
    std::cout << "does not contain 24" << std::endl;
  }

  if (s1.contains(0)) {
    std::cout << "contains 0" << std::endl;
  }

  return EXIT_SUCCESS;
}
