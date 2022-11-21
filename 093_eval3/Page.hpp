#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
class Page {
 private:
  size_t pagenum;
  std::string filename;
  char type;
  std::vector<std::pair<size_t, std::string> > options;

 public:
  Page() {}
  Page(size_t _pn, std::string _fn, char _t) : pagenum(_pn), filename(_fn), type(_t) {}

  void addOption(size_t pn, std::string message) {
    options.push_back(std::pair<size_t, std::string>(pn, message));
  }

  const size_t & getPage() const { return pagenum; }
  const std::string & getFileName() const { return filename; }
  void printPage(std::string dir) {
    std::ifstream ifs;
    std::string line;
    std::string fname = dir + "/" + filename;
    ifs.open(fname.c_str(), std::ifstream::in);
    while (!ifs.eof()) {
      std::getline(ifs, line);
      std::cout << line << std::endl;
    }
  }

  void printOptions() {
    if (type == 'N') {
      std::cout << "What would you like to do?" << std::endl;
      std::cout << std::endl;
      for (size_t i = 0; i < options.size(); i++) {
        std::cout << " " << i + 1 << ". " << options[i].second << std::endl;
      }
    }
    else if (type == 'W') {
      std::cout << "Congratulations! You have won. Hooray!" << std::endl;
    }
    else {
      std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
    }
  }
};
