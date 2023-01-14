#include "point.hpp"

#include <cmath>
#include <cstdio>

Point::Point() : x(0), y(0) {
}
Point::Point(double init_x, double init_y) : x(init_x), y(init_y) {
}
Point::~Point() {
}

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  double ans;
  ans = sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
  return ans;
}
