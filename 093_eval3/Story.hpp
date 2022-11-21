#include <fstream>

#include "Page.hpp"

class Story {
  std::vector<Page> pages;

  void parseLine(std::string line) {
    size_t f_at = line.find('@');
    size_t f_coma = line.find(':');
    // char * endptr;
    if (f_at != std::string::npos) {
      size_t pagenum = strtoul(line.c_str(), NULL, 0);
      char typ = line[f_at + 1];
      std::string fname = line.substr(f_coma + 1);
      pages.push_back(Page(pagenum, fname, typ));
    }
    else {
      size_t cur_page = strtoul(line.c_str(), NULL, 0);
      size_t next_page = strtoul(line.substr(f_coma + 1).c_str(), NULL, 0);
      size_t f_coma2 = line.find_last_of(':');
      std::string message = line.substr(f_coma2 + 1);
      for (size_t i = 0; i < pages.size(); i++) {
        if (pages[i].getPage() == cur_page) {
          pages[i].addOption(next_page, message);
          break;
        }
      }
    }
  }

  //  void parseLine(const char * line) {
  //if (strchr(line, '@')!= NULL)

  //}

 public:
  Story(std::string dir) {
    std::string fname = dir + "/story.txt";
    buildStory(fname.c_str());
  }
  void buildStory(const char * fname) {
    std::ifstream ifs;
    std::string line;
    //char * line;
    ifs.open(fname, std::ifstream::in);
    while (!ifs.eof()) {
      std::getline(ifs, line);
      if (line.compare("") != 0) {
        parseLine(line);
      }
    }
  }

  void printStory(std::string dir) {
    for (size_t i = 0; i < pages.size(); i++) {
      std::cout << "Page " << pages[i].getPage() << std::endl;
      std::cout << "==========" << std::endl;
      pages[i].printPage(dir);
      pages[i].printOptions();
    }
  }
};
