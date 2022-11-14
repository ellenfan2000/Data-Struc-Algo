#include <cstdio>
#include <cstdlib>

#include "bstmap.h"

int main(void) {
  BstMap<int, int> map1;
  map1.add(3, 4);
  map1.add(5, 6);
  map1.add(2, 5);
  map1.add(19, 2);
  map1.add(1, 35);
  map1.print();
  std::cout << "\n";
  map1.remove(19);

  map1.remove(1);
  map1.print();
  std::cout << "\n";
  std::cout << "Look up (5,6), result is " << map1.lookup(5) << std::endl;
  map1.add(1, 12);
  std::cout << "Look up (19,1), result is " << map1.lookup(1) << std::endl;
}
