#include <fstream>
#include <map>
#include <queue>
#include <set>
#include <sstream>

#include "Page.hpp"

/*
pages: a vector of pages
dir: the directory name of the input story
variables: map of <string, long>, stores the each varibale's value when play in step 4
 */
class Story {
  std::vector<Page> pages;
  std::string dir;
  std::map<std::string, long> variables;

  // parse the line pagenumber@type:filename
  void initialPage(std::string & line) {
    size_t idx = 0;
    size_t pn1 = myStrtoul(line, &idx, 10);  //idx = index of '@' sign

    //page not defined in order
    if (pn1 != pages.size()) {
      throw InvalidPageOrder();
    }
    char type = line[idx + 1];

    if (type != 'N' && type != 'W' && type != 'L') {
      throw InvalidLine(line);
    }

    if (line[idx + 2] != ':') {
      throw InvalidLine(line);
    }
    std::string filename = line.substr(idx + 3);
    if (filename.empty()) {
      throw CannotOpenFile(filename);
    }
    std::ifstream ifs;
    std::string fname = dir + "/" + filename;
    //check if file existed
    ifs.open(fname.c_str(), std::ifstream::in);
    if (!ifs.good()) {
      throw CannotOpenFile(fname);
    }
    pages.push_back(Page(pn1, fname, type));
  }

  //parse the line: pagenumber$variable=value
  void setVariables(std::string & line) {
    size_t idx = 0;
    size_t pn1 = myStrtoul(line, &idx, 10);  //first page number
    size_t f_equal = line.find('=', idx);    //index of '=' sign

    if (f_equal != std::string::npos) {
      std::string var = line.substr(idx + 1, f_equal - idx - 1);
      std::string sub = line.substr(f_equal + 1);  //string after '='sign

      //whether value is not empty
      bool flag = false;
      for (size_t i = 0; i < sub.size(); i++) {
        if (!isspace(sub[i])) {
          flag = true;
          long value = myStrtol(sub, &idx, 10);
          // if there are still characters after value
          if (idx < sub.size()) {
            throw InvalidLine(line);
          }
          pages[pn1].setPageVaribale(var, value);
          variables[var] = 0;
          break;
        }
      }
      //value is empty
      if (!flag) {
        throw InvalidLine(line);
      }
    }
    else {  //no '=' sign in the line
      throw InvalidLine(line);
    }
  }

  //parse the line: pagenumber:nextpage:message
  void setPageOptions(std::string & line) {
    size_t idx = 0;
    size_t pn1 = myStrtoul(line, &idx, 10);  //idx = index of the first colon
    size_t colon2 = 0;

    std::string sub = line.substr(idx + 1);  //string after first colon

    size_t pn2 = myStrtoul(sub, &colon2, 10);  //colon2 = index of the second colon
    if (sub[colon2] != ':') {
      throw InvalidLine(line);
    }

    std::string message = sub.substr(colon2 + 1);
    pages[pn1].addOption(pn2, message);
  }

  //parse the line: pagenumber[var=value]:nextpage:message
  void setPageVarOption(std::string & line) {
    size_t idx = 0;
    size_t pn1 = myStrtoul(line, &idx, 10);  //idx = index of the '['
    size_t f_equal = line.find('=', idx);    //index of the '=' sign

    if (f_equal != std::string::npos) {
      std::string var;
      //empty variable name
      if (f_equal == idx + 1) {
        var = "";
      }
      var = line.substr(idx + 1, f_equal - idx - 1);

      size_t pos = 0;
      std::string sub1 =
          line.substr(f_equal + 1);  //string after '=' sign, value]:nextpage:message
      long value = myStrtol(sub1, &pos, 10);  //pos is the first char after number

      //if exist char between value and ']:', error
      if (sub1[pos] != ']' && sub1[pos + 1] != ':') {
        throw InvalidLine(line);
      }

      std::string sub2 = sub1.substr(pos + 2);  //string after ']:', nextpage:message
      size_t pn2 = myStrtoul(sub2, &pos, 10);   //pos=index of ':'
      if (sub2[pos] != ':') {
        throw InvalidLine(line);
      }
      std::string message = sub2.substr(pos + 1);
      pages[pn1].addOption(pn2, message, value, var);
    }
    else {  //if '=' does not exist, throw exception
      throw InvalidLine(line);
    }
  }

  //parse line read from story.txt, integrate four kinds of lines
  void parseLine(std::string line) {
    size_t idx = 0;
    size_t pn1 = myStrtoul(line, &idx, 10);

    //differenciate line by the first char after number(page number 1)
    if (line[idx] == '@') {  //number@type:filename
      initialPage(line);
    }
    else {
      //all the set option lines
      //if set option before page defined, throw error
      if (pn1 >= pages.size()) {
        throw InvalidBuildOrder();
      }
      //if page is a Win or Lose page, throw error
      if (pages[pn1].type == 'W' || pages[pn1].type == 'L') {
        throw InvalidOptionSet(line);
      }
      if (line[idx] == '$') {  //pagenumber$var=value
        setVariables(line);
      }
      else if (line[idx] == ':') {  //pagenumber:destpage:text
        setPageOptions(line);
      }
      else if (line[idx] == '[') {  //pagenumber[var=value]:dest:texto
        setPageVarOption(line);
      }
      else {
        throw InvalidLine(line);
      }
    }
  }

  //Every page that is referenced by a choice is valid
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

  //Every page (except page 0) is referenced by at least one *other* page's choices.
  bool checkCoverage() {
    //count how many times a page is referenced
    std::vector<int> coverage(pages.size(), 0);
    for (size_t i = 0; i < pages.size(); i++) {
      for (size_t j = 0; j < pages[i].options.size(); j++) {
        coverage[pages[i].options[j].nextpage] += 1;
      }
    }
    for (size_t k = 1; k < coverage.size(); k++) {
      if (coverage[k] == 0) {
        return false;
      }
    }
    return true;
  }

  //At least one page must be a WIN page and at least one page must be a LOSE page.
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
    std::ifstream ifs;
    std::string line;
    ifs.open(fname.c_str(), std::ifstream::in);
    if (ifs.good()) {
      while (!ifs.eof()) {
        std::getline(ifs, line);
        //jump an empty line
        if (line.compare("") != 0) {
          //jump a line with only white space
          for (size_t i = 0; i < line.size(); i++) {
            if (!isspace(line[i])) {
              parseLine(line);
              break;
            }
          }
        }
      }
    }
    else {
      throw CannotOpenFile(fname);
    }
  }

  //print the story
  void printStory() {
    for (size_t i = 0; i < pages.size(); i++) {
      std::cout << "Page " << pages[i].pagenum << std::endl;
      std::cout << "==========" << std::endl;
      pages[i].printPage();
      std::map<size_t, bool> * valid = pages[i].printOptions(variables);
      delete valid;
    }
  }

  //check if story is a whole
  bool checkValidStory() {
    if (checkChoics() && checkCoverage() && checkEndGame()) {
      return true;
    }
    return false;
  }

  //play the story
  void play() {
    size_t cur = 0;
    size_t next;
    //whether each choice can be chosen
    std::map<size_t, bool> * valid;
    while (pages[cur].type != 'W' && pages[cur].type != 'L') {
      pages[cur].printPage();
      //update varibales with the one store in each page
      std::map<std::string, long int>::iterator it;
      if (pages[cur].variables.size() != 0) {
        for (it = pages[cur].variables.begin(); it != pages[cur].variables.end(); ++it) {
          variables[it->first] = it->second;
        }
      }
      valid = pages[cur].printOptions(variables);
      std::string input;
      //keep asking user to input option until gets a valid one
      while (true) {
        std::getline(std::cin, input);
        size_t pos;
        try {  //input is not a number
          next = myStrtoul(input, &pos, 10);
        }
        catch (InvalidNumber & e) {
          next = 0;
        }
        if (next < 1 || next > pages[cur].options.size() || input.size() != pos) {
          std::cout << "That is not a valid choice, please try again" << std::endl;
        }
        else if (!(*valid)[next - 1]) {
          std::cout << "That choice is not available at this time, please try again"
                    << std::endl;
        }
        else {
          break;
        }
      }
      cur = pages[cur].options[next - 1].nextpage;
      delete valid;
    }
    pages[cur].printPage();
    valid = pages[cur].printOptions(variables);
    delete valid;
  }

  /*
    path: (choice number, page number the option leads to)
    the function prints the according path following the format:
    1(1),2(3),3(1),4(2),5(3),6(1),7(win)
  */
  void printPath(std::vector<std::pair<size_t, size_t> > & path) {
    std::cout << pages[path[0].second].pagenum;
    for (size_t i = 1; i < path.size(); i++) {
      std::cout << "(" << path[i].first << ")," << pages[path[i].second].pagenum;
    }
    std::cout << "(win)" << std::endl;
  }

  /*
    find all cycle-free path to win
    if cannot win, print unwinnable 
  */
  void findWin() {
    //stores each path that is going to visit
    std::queue<std::vector<std::pair<size_t, size_t> > > todo;
    //stores each page that is visited
    std::set<size_t> visited;
    //whether the game is winnable;
    bool flag = false;
    todo.push(
        std::vector<std::pair<size_t, size_t> >(1, std::pair<size_t, size_t>(1, 0)));
    while (todo.size() > 0) {
      std::vector<std::pair<size_t, size_t> > currentPath = todo.front();
      todo.pop();

      //current page is the last item in the path
      Page * currentPage = &pages[currentPath.back().second];
      if (currentPage->type == 'W') {  // if win
        printPath(currentPath);
        flag = true;
      }
      /*if current page not in visited:
	for each of its choice, create a new path with corresponding next page number
	append to current path, and push the new path to the todo queue
      */
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
