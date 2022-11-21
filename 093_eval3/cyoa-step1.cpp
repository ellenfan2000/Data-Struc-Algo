#include <cstdlib>
#include <iostream>
#include <string>

#include "Story.hpp"
int main(int argc, char ** argv) {
  if (argc == 2) {
    std::string dir = argv[1];
    Story sto(dir);
    sto.printStory(dir);
  }
}
