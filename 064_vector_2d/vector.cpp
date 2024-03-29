#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */

void Vector2D::initVector(double init_x, double init_y) {
  x = init_x;
  y = init_y;
}

double Vector2D::getMagnitude() const {
  double ans = sqrt(x * x + y * y);
  return ans;
}

Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D ans;
  ans.initVector(x, y);
  ans.x += rhs.x;
  ans.y += rhs.y;
  return ans;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
}

double Vector2D::dot(const Vector2D & rhs) const {
  double ans = x * rhs.x + y * rhs.y;
  return ans;
}

void Vector2D::print() const {
  std::printf("<%.2f, %.2f>", x, y);
}
