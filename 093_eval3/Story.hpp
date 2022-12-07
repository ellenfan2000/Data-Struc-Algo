#include <fstream>
#include <map>
#include <queue>
#include <set>
#include <sstream>

#include "Page.hpp"

class Story {
  std::vector<Page> pages;
  std::string dir;
  std::map<std::string, long int> variables;

  long my_strtol(std::string str, size_t * idx = 0, int base = 10) {
    const char * string = str.c_str();
    char * endptr;
    long ans = strtol(string, &endptr, base);
    if (idx) {
      *idx = endptr - string;
    }
    return ans;
  }

  unsigned long my_strtoul(std::string str, size_t * idx = 0, int base = 10) {
    const char * string = str.c_str();
    char * endptr;
    unsigned long ans = strtoul(string, &endptr, base);
    if (idx) {
      *idx = endptr - string;
    }
    return ans;
  }

  void parseLine(std::string line) {
    size_t idx = 0;
    size_t pn1 = my_strtoul(line, &idx, 10);

    if (line[idx] == '@') {  //number@type:filename
      if (pn1 != pages.size()) {
        throw "invalid page declaration order!";
      }

      char type = line[idx + 1];

      if (type != 'N' && type != 'W' && type != 'L') {
        throw "Wrong line with invlid type";
        // exit(EXIT_FAILURE);
      }

      if (line[idx + 2] != ':') {
        throw "Wrong line with invlid type";
        // exit(EXIT_FAILURE);
      }

      std::string fname = line.substr(idx + 3);

      pages.push_back(Page(pn1, fname, type));
    }
    else {
      if (pn1 >= pages.size()) {
        throw "Invalid order, varibale setting before page build";
        // exit(EXIT_FAILURE);
      }

      if (line[idx] == '$') {  //pagenumber$var=value
        size_t f_equal = line.find('=', idx);
        if (f_equal != std::string::npos) {
          std::string var =
              line.substr(idx + 1, f_equal - idx - 1);  //is ""possible var??
          long int value = my_strtol(line.substr(f_equal + 1), NULL, 10);
          pages[pn1].setPageVaribale(var, value);
          variables[var] = 0;
        }
        else {
          throw "Invalid varibale setting";
        }
      }

      else if (line[idx] == ':') {  //pagenumber:destpage:text
        size_t comma2 = 0;

        std::string sub = line.substr(idx + 1);

        size_t pn2 = my_strtoul(sub, &comma2, 10);
        if (sub[comma2] != ':') {
          throw "invalid option declaration";
          exit(EXIT_FAILURE);
        }

        std::string message = sub.substr(comma2 + 1);
        pages[pn1].addOption(pn2, message);
      }
      else if (line[idx] == '[') {  //pagenumber[var=value]:dest:text
        size_t f_equal = line.find('=', idx);

        if (f_equal != std::string::npos) {
          std::string var =
              line.substr(idx + 1, f_equal - idx - 1);  //is ""possible var??
          size_t pos = 0;
          std::string sub1 = line.substr(f_equal + 1);
          long value = my_strtol(sub1, &pos, 10);
          if (sub1[pos] != ']' && sub1[pos + 1] != ':') {
            throw "Invalid varibale declaration";
            exit(EXIT_FAILURE);
          }

          std::string sub2 = sub1.substr(pos + 2);
          size_t pn2 = my_strtoul(sub2, &pos, 10);
          if (sub2[pos] != ':') {
            throw "Invalid varibale declaration";
            exit(EXIT_FAILURE);
          }
          std::string message = sub2.substr(pos + 1);
          pages[pn1].addOption(pn2, message, value, var);
        }
        else {
          throw "Invalid varibale declaration";
          exit(EXIT_FAILURE);
        }
      }
      else {
        throw "wrong story!";
      }
    }
  }

  void buildStory(const char * fname) {
    std::ifstream ifs;
    std::string line;
    ifs.open(fname, std::ifstream::in);
    while (!ifs.eof()) {
      std::getline(ifs, line);
      if (line.compare("") != 0) {
        parseLine(line);
      }
    }
  }

  bool checkChoics() {
    for (size_t i = 0; i < pages.size(); i++) {
      for (size_t j = 0; j < pages[i].options.size(); j++) {
        if (pages[i].options[j].nextpage > pages.size() - 1 ||
            pages[i].options[j].nextpage < 0) {
          return false;
        }
      }
    }
    return true;
  }

  bool checkCoverage() {
    std::vector<int> coverage(pages.size(), 0);
    for (size_t i = 0; i < pages.size(); i++) {
      for (size_t j = 0; j < pages[i].options.size(); j++) {
        coverage[pages[i].options[j].nextpage] = 1;
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

  void printStory() {
    for (size_t i = 0; i < pages.size(); i++) {
      std::cout << "Page " << pages[i].pagenum << std::endl;
      std::cout << "==========" << std::endl;
      pages[i].printPage(dir);
      pages[i].printOptions(variables);
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
    std::map<size_t, bool> * valid;
    while (pages[cur].type != 'W' && pages[cur].type != 'L') {
      pages[cur].printPage(dir);

      std::map<std::string, long int>::iterator it;
      if (pages[cur].variables.size() != 0) {
        for (it = pages[cur].variables.begin(); it != pages[cur].variables.end(); ++it) {
          variables[it->first] = it->second;
        }
      }

      valid = pages[cur].printOptions(variables);
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

        else if (!(*valid)[next - 1]) {
          std::cout << "That choice is not available at this time, please try again"
                    << std::endl;
          std::cin >> next;
        }
        else {
          break;
        }
      }

      cur = pages[cur].options[next - 1].nextpage;
      delete valid;
    }
    pages[cur].printPage(dir);
    valid = pages[cur].printOptions(variables);
    delete valid;
    //exit(EXIT_SUCCESS);
  }

  void printPath(std::vector<std::pair<size_t, size_t> > & path) {
    //std::stringstream s;
    std::cout << pages[path[0].second].pagenum;
    for (size_t i = 1; i < path.size(); i++) {
      std::cout << "(" << path[i].first << ")," << pages[path[i].second].pagenum;
    }
    std::cout << "(win)" << std::endl;
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
          temp.push_back(
              std::pair<size_t, size_t>(i + 1, currentPage->options[i].nextpage));
          todo.push(temp);
        }
      }
    }
    if (!flag) {
      std::cout << "This story is unwinnable!" << std::endl;
    }
  }
};
