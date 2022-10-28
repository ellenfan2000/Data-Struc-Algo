#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>
template<typename T>

class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0) {}
  Matrix(int r, int c) : numRows(r), numColumns(c) {
    for (int i = 0; i < r; i++) {
      rows.push_back(std::vector<T>(c));
    }
  }
  Matrix(const Matrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) {
    rows = rhs.rows;
  }
  ~Matrix() {}
  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      rows = rhs.rows;
    }
    return *this;
  }
  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows);
    return rows[index];
  }
  std::vector<T> & operator[](int index) {
    assert(index >= 0 && index < numRows);
    return rows[index];
  }
  bool operator==(const Matrix & rhs) const {
    if (numColumns != rhs.numColumns || numRows != rhs.numRows) {
      return false;
    }
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        if (rows[i][j] != rhs.rows[i][j]) {
          return false;
        }
      }
    }
    return true;
  }
  Matrix<T> operator+(const Matrix<T> & rhs) const {
    assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
    Matrix<T> ans(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        ans[i][j] = (*this)[i][j] + rhs[i][j];
      }
    }
    return ans;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  if (rhs.getRows() == 0) {
    s << "[  ]";
    return s;
  }
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << "{";
    for (int j = 0; j < rhs.getColumns() - 1; j++) {
      s << rhs[i][j] << ", ";
    }
    if (i == rhs.getRows() - 1) {
      s << rhs[i][rhs.getColumns() - 1] << "} ]";
    }
    else {
      s << rhs[i][rhs.getColumns() - 1] << "},\n";
    }
  }

  return s;
}
//YOUR CODE GOES HERE!

#endif
