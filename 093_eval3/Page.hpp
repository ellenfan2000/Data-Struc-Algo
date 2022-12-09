#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "functions.hpp"

/*
pagenum: this page's pagenum
filename: the file this pages's content located
type: N, L, W
options: vector of Choices, all choices the page can lead to
variables: if user get to this page, what each varibale would be  
*/

class Page {
 private:
  /*
   type: whether the choice depend on variables
   nextpage: the page number this choice leads to
   message: messsage of the choice
   value, varibale: when variable = value, print the choice
   */
  class Choice {
   public:
    char type;
    size_t nextpage;
    std::string message;
    long int value;
    std::string varibale;

    Choice(size_t np, std::string mess) :
        type('N'), nextpage(np), message(mess), value(0), varibale("") {}
    Choice(size_t np, std::string mess, long int val, std::string var) :
        type('V'), nextpage(np), message(mess), value(val), varibale(var) {}
  };
  size_t pagenum;
  std::string filename;
  char type;
  std::vector<Choice> options;
  std::map<std::string, long> variables;

 public:
  Page() {}
  Page(size_t _pn, std::string _fn, char _t) : pagenum(_pn), filename(_fn), type(_t) {}

  //choice does not depend on variables
  void addOption(size_t pn, std::string message) {
    options.push_back(Choice(pn, message));
  }
  //choices that depend on variable values
  void addOption(size_t np, std::string mess, long int val, std::string var) {
    options.push_back(Choice(np, mess, val, var));
  }

  void setPageVaribale(std::string var, long int val) { variables[var] = val; }

  //print page's content
  void printPage() {
    std::ifstream ifs;
    std::string line;
    ifs.open(filename.c_str(), std::ifstream::in);
    if (ifs.good()) {
      while (!ifs.eof()) {
        std::getline(ifs, line);
        std::cout << line << std::endl;
      }
    }
    else {
      throw CannotOpenFile(filename);
    }
  }
  /*
    vars: current value of each variable when playing the game
    this function print pages's options and return a map of whether each choice can be chosen
    based on current varibales' value
  */
  std::map<size_t, bool> * printOptions(std::map<std::string, long int> vars) {
    //{choice number: whether it can be chosen, ...}
    std::map<size_t, bool> * valid = new std::map<size_t, bool>;
    if (type == 'N') {
      std::cout << "What would you like to do?" << std::endl;
      std::cout << std::endl;

      for (size_t i = 0; i < options.size(); i++) {
        if (options[i].type == 'N') {  //normal choice does not depend on variable
          std::cout << i + 1 << "." << options[i].message << std::endl;
          (*valid)[i] = true;
        }
        else {  //choices that can be chosen
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
};
