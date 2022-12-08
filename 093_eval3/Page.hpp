#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "functions.h"
class Page {
 private:
  class Choice {
   public:
    size_t nextpage;
    std::string message;
    long int value;
    std::string varibale;

    Choice(size_t np, std::string mess) :
        nextpage(np), message(mess), value(0), varibale("") {}
    Choice(size_t np, std::string mess, long int val, std::string var) :
        nextpage(np), message(mess), value(val), varibale(var) {}
  };
  size_t pagenum;
  std::string filename;
  char type;
  std::vector<Choice> options;
  std::map<std::string, long int> variables;

 public:
  Page() {}
  Page(size_t _pn, std::string _fn, char _t) : pagenum(_pn), filename(_fn), type(_t) {}

  void addOption(size_t pn, std::string message) {
    options.push_back(Choice(pn, message));
  }

  void addOption(size_t np, std::string mess, long int val, std::string var) {
    options.push_back(Choice(np, mess, val, var));
  }

  void setPageVaribale(std::string var, long int val) { variables[var] = val; }

  void printPage(std::string dir) {
    std::ifstream ifs;
    std::string line;
    std::string fname = dir + "/" + filename;
    ifs.open(fname.c_str(), std::ifstream::in);
    if (ifs.good()) {
      while (!ifs.eof()) {
        std::getline(ifs, line);
        std::cout << line << std::endl;
      }
    }
    else {
      throw CannotOpenFile(fname);
    }
  }

  std::map<size_t, bool> * printOptions(std::map<std::string, long int> vars) {
    std::map<size_t, bool> * valid = new std::map<size_t, bool>;
    if (type == 'N') {
      std::cout << "What would you like to do?" << std::endl;
      std::cout << std::endl;

      for (size_t i = 0; i < options.size(); i++) {
        if (options[i].varibale.compare("") == 0) {
          std::cout << i + 1 << "." << options[i].message << std::endl;
          (*valid)[i] = true;
        }
        else {
          if (vars[options[i].varibale] == options[i].value) {
            std::cout << i + 1 << "." << options[i].message << std::endl;
            (*valid)[i] = true;
          }
          else {
            std::cout << i + 1 << "."
                      << "<UNAVAILABLE>" << std::endl;
            (*valid)[i] = false;
          }
        }
      }
    }
    else if (type == 'W') {
      std::cout << "Congratulations! You have won. Hooray!" << std::endl;
    }
    else {
      std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
    }
    return valid;
  }

  friend class Story;
  friend class Story2;
};
