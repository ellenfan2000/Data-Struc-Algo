#include <exception>
#include <iostream>

class InvalidStoryFile : public std::exception {
 public:
  virtual const char * what() const throw() { return "Content errors in story.txt"; }
};
class InvalidPageOrder : public InvalidStoryFile {
 public:
  virtual const char * what() const throw() { return "Pages not defined in order"; }
};

class InvalidLine : public InvalidStoryFile {
 private:
  std::string line;

 public:
  InvalidLine(std::string _line) throw() : line(_line) {}
  virtual const char * what() const throw() {
    std::cerr << "Invalid line format in story.txt: " << std::endl;
    return line.c_str();
  }
  ~InvalidLine() throw() {}
};
class InvalidOptionSet : public InvalidStoryFile {
 private:
  std::string line;

 public:
  InvalidOptionSet(std::string _line) throw() : line(_line) {}
  virtual const char * what() const throw() {
    std::cerr << "Invalid Option: Win and Lose page should not have options "
              << std::endl;
    return line.c_str();
  }
  ~InvalidOptionSet() throw() {}
};

class InvalidBuildOrder : public InvalidStoryFile {
 public:
  virtual const char * what() const throw() {
    return "Choice setting before page setting";
  }
};
class CannotOpenFile : public std::exception {
 private:
  std::string fname;

 public:
  CannotOpenFile(std::string f) throw() : fname(f) {}
  virtual const char * what() const throw() {
    std::cerr << "Cannot open file: ";
    return fname.c_str();
  }
  ~CannotOpenFile() throw() {}
};
class InvalidNumber : public std::exception {
 private:
  std::string number;

 public:
  InvalidNumber(std::string _line) throw() : number(_line) {}
  virtual const char * what() const throw() {
    std::cerr << "Invalid number to convert: ";
    return number.c_str();
  }
  ~InvalidNumber() throw() {}
};
