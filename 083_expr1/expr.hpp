#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

class Expression {
 public:
  virtual ~Expression() {}
  virtual std::string toString() const = 0;
};

class NumExpression : public Expression {
 private:
  long oprand;

 public:
  NumExpression(long x) : oprand(x) {}
  virtual ~NumExpression() {}
  virtual std::string toString() const {
    std::stringstream s;
    s << oprand;
    std::string ans = s.str();
    return ans;
  };
};

class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
  virtual std::string toString() const {
    std::stringstream s;
    s << "(" << lhs->toString() << " + " << rhs->toString() + ")";
    std::string ans = s.str();
    return ans;
  };
};
