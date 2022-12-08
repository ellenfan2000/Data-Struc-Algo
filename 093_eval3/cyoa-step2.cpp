#include <cstdlib>
#include <iostream>
#include <string>

#include "Story.hpp"
int main(int argc, char ** argv) {
  if (argc == 2) {
    std::string dir = argv[1];
    try {
      Story sto(dir);
      if (sto.checkValidStory()) {
        // sto.printStory(dir);
        sto.play();
      }
      else {
        std::cerr << "Not playable story" << std::endl;
      }
    }
    catch (InvalidStoryFile & e) {
      std::cerr << e.what() << std::endl;
      return EXIT_FAILURE;
    }
    catch (CannotOpenFile & e) {
      std::cerr << e.what() << std::endl;
      return EXIT_FAILURE;
    }
  }
  else {
    std::cerr << "Usage: program dir" << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
