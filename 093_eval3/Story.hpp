#include <fstream>
#include <queue>
#include <set>
#include <sstream>

#include "Page.hpp"

class Story {
  std::vector<Page> pages;
  std::string dir;
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

  // bool validChoice(size_t c, Page & p) {
  //   for (size_t i = 0; i < p.options.size(); i++) {
  //     if (c == p.options[i].first) {
  //       return true;
  //     }
  //   }
  //   return false;
  // }

  bool checkChoics() {
    for (size_t i = 0; i < pages.size(); i++) {
      for (size_t j = 0; j < pages[i].options.size(); j++) {
        if (pages[i].options[j].first > pages.size() - 1 ||
            pages[i].options[j].first < 0) {
          return false;
        }
      }
      // for (std::map<size_t, std::string>::iterator it = pages[i].options.begin();
      //      it != pages[i].options.end();
      //      ++it) {
      //   if (it->first > pages.size() - 1 || it->first < 0) {
      //     return false;
      //   }
      // }
    }
    return true;
  }

  bool checkCoverage() {
    std::vector<int> coverage(pages.size(), 0);
    for (size_t i = 0; i < pages.size(); i++) {
      for (size_t j = 0; j < pages[i].options.size(); j++) {
        coverage[pages[i].options[j].first] = 1;
      }
    }
    for (size_t k = 1; k < coverage.size(); k++) {
      if (coverage[k] == 0) {
        return false;
      }
    }
    return true;
  }

  bool checkEndGame() {
    int win = 0;
    int lose = 0;
    for (size_t i = 0; i < pages.size(); i++) {
      if (pages[i].type == 'W') {
        win++;
      }
      if (pages[i].type == 'L') {
        lose++;
      }
    }

    if (win > 0 && lose > 0) {
      return true;
    }

    return false;
  }

 public:
  Story(std::string _dir) {
    dir = _dir;
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

  void printStory() {
    for (size_t i = 0; i < pages.size(); i++) {
      std::cout << "Page " << pages[i].pagenum << std::endl;
      std::cout << "==========" << std::endl;
      pages[i].printPage(dir);
      pages[i].printOptions();
    }
  }

  bool checkValidStory() {
    if (checkChoics() && checkCoverage() && checkEndGame()) {
      return true;
    }
    return false;
  }

  void play() {
    size_t cur = 0;
    size_t next;
    while (pages[cur].type != 'W' && pages[cur].type != 'L') {
      pages[cur].printPage(dir);
      pages[cur].printOptions();
      std::cin >> next;

      while (true) {
        if (!std::cin.good()) {
          std::cin.clear();
          std::cin.ignore();
          std::cout << "That is not a valid choice, please try again" << std::endl;
          std::cin >> next;
        }
        else if (next < 1 || next > pages[cur].options.size()) {
          std::cout << "That is not a valid choice, please try again" << std::endl;
          std::cin >> next;
        }
        else {
          break;
        }
      }

      cur = pages[cur].options[next - 1].first;
    }
    pages[cur].printPage(dir);
    pages[cur].printOptions();
    //exit(EXIT_SUCCESS);
  }
  void printPath(std::vector<std::pair<size_t, size_t> > & path) {
    //std::stringstream s;
    std::cout << pages[path[0].second].pagenum;
    for (size_t i = 1; i < path.size(); i++) {
      std::cout << "(" << path[i].first << "), " << pages[path[i].second].pagenum;
    }
    std::cout << "(W)" << std::endl;
  }

  void findWin() {
    // std::vector<std::vector<Page *> > allPath;
    std::queue<std::vector<std::pair<size_t, size_t> > > todo;
    std::set<size_t> visited;
    bool flag = false;
    todo.push(
        std::vector<std::pair<size_t, size_t> >(1, std::pair<size_t, size_t>(1, 0)));
    while (todo.size() > 0) {
      std::vector<std::pair<size_t, size_t> > currentPath = todo.front();
      todo.pop();
      Page * currentPage = &pages[currentPath.back().second];
      if (currentPage->type == 'W') {
        printPath(currentPath);
        flag = true;
      }
      if (visited.find(currentPage->pagenum) == visited.end()) {
        visited.insert(currentPage->pagenum);
        for (size_t i = 0; i < currentPage->options.size(); i++) {
          std::vector<std::pair<size_t, size_t> > temp = currentPath;
          temp.push_back(std::pair<size_t, size_t>(i + 1, currentPage->options[i].first));
          todo.push(temp);
        }
      }
    }
    if (!flag) {
      std::cout << "This story is unwinnable!" << std::endl;
    }
  }
};
