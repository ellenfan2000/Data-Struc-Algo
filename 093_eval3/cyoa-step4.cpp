#include <cstdlib>
#include <iostream>
#include <string>

#include "Story.hpp"
int main(int argc, char ** argv) {
  if (argc == 2) {
    std::string dir = argv[1];
    Story sto(dir);

    if (sto.checkValidStory()) {
      // sto.printStory(dir);
      sto.play();
    }
  }
  return EXIT_SUCCESS;
}
