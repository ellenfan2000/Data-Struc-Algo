#include "circle.hpp"

#include <cmath>
#include <cstdio>

Circle::Circle(Point p, double r) : center(p), radius(r) {
}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double min(double a, double b) {
  if (a <= b) {
    return a;
  }
  else {
    return b;
  }
}

double max(double a, double b) {
  if (a >= b) {
    return a;
  }
  else {
    return b;
  }
}
double Circle::intersectionArea(const Circle & otherCircle) {
  double ans = 0;
  double d = center.distanceFrom(otherCircle.center);
  double r1 = max(radius, otherCircle.radius);
  double r2 = min(radius, otherCircle.radius);
  double d1 = (pow(r1, 2) - pow(r2, 2) + pow(d, 2)) / (2 * d);
  double d2 = d - d1;
  if (d >= r1 + r2) {
    ans = 0;
  }
  else if (d <= r1 - r2) {
    ans = acos(-1) * pow(min(radius, otherCircle.radius), 2);
  }
  else {
    ans = pow(r1, 2) * acos(d1 / r1) - d1 * sqrt(pow(r1, 2) - pow(d1, 2)) +
          pow(r2, 2) * acos(d2 / r2) - d2 * sqrt(pow(r2, 2) - pow(d2, 2));
  }

  return ans;
}
