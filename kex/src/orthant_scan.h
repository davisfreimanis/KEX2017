#include "point.h"
#include <iostream> // std::cout, std::endl
#include <vector> // std::vector
#include <algorithm> // std::sort, std::set_intersection

#ifndef KEX2017_ORTHANT_SCAN_H
#define KEX2017_ORTHANT_SCAN_H

bool pointInTriangle(Point a, Point b, Point c, Point p);
Point findCenter(Point *points, int size, Point center);

#endif //KEX2017_ORTHANT_SCAN_H



