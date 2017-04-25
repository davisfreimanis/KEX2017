#ifndef KEX_POINT_H
#define KEX_POINT_H

#include <iostream>

class Point {

public:
    Point();

    Point(double x, double y);

    bool operator<(Point b);

    double x;
    double y;
};

bool operator==(Point &, Point &);
bool operator!=(Point &, Point &);
//Point operator+(const Point &);


#endif //KEX_POINT_H