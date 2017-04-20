#include "point.h"
#include "orthant_scan.h"
#include <iostream> // std::cout, std::endl
#include <vector> // std::vector
#include <algorithm> // std::sort, std::set_intersection

using namespace std;

/*
 * Checks if point p is inside triangle made of a, b and c
 * http://stackoverflow.com/a/14382692
 */
bool pointInTriangle(Point a, Point b, Point c, Point p) {
    double area = 0.5 * (-b.y*c.x + a.y*(-b.x + c.x) + a.x * (b.y - c.y) + b.x * c.y);
    double s = 1 / (2 * area) * (a.y*c.x - a.x * c.y + (c.y - a.y) * p.x + (a.x - c.x) * p.y);
    double t = 1 / (2 * area) * (a.x*b.y - a.y * b.x + (a.y - b.y) * p.x + (b.x - a.x) * p.y);

    return s > 0 && t > 0 && 1-s-t > 0;
}

/*
 * Returns the center of all the points.
 */
Point findCenter(Point *points, int size, Point center) {
    double x = 0;
    double y = 0;
    for (int i = 0; i < size; ++i) {
        x += points[i].x;
        y += points[i].y;
    }
    center.x = x/size;
    center.y = y/size;

    return center;
}