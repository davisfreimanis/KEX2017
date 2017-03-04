#ifndef KEX_POINT_H
#define KEX_POINT_H

#include <iostream>

class Point {

 public:
  Point();
  Point(double x, double y);

 private:
  double x;
  double y;
};

//Point operator+(const Point &);


#endif //KEX_POINT_H