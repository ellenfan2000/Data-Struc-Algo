class Point {
 private:
  double x;
  double y;

 public:
  Point();
  Point(double init_x, double init_y);
  ~Point();

  void move(double dx, double dy);

  double distanceFrom(const Point & p);
};
