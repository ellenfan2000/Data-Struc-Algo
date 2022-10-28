#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
void sortLines(std::istream & s) {
  std::string line;
  std::vector<std::string> lines;
  if (!s.good()) {
    s.clear();
    std::cerr << "Wrong input" << std::endl;
    exit(EXIT_FAILURE);
  }
  while (!s.eof()) {
    std::getline(s, line);
    lines.push_back(line);
  }
  std::sort(lines.begin(), lines.end());
  for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it) {
    std::cout << *it << std::endl;
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    sortLines(std::cin);
  }
  else {
    for (int i = 1; i < argc; i++) {
      const char * fname = argv[i];
      std::ifstream ifs;
      ifs.open(fname, std::ifstream::in);
      sortLines(ifs);
    }
  }
  return EXIT_SUCCESS;
}
