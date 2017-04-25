#include "point.h"
#include <iostream>
#include <string>

/**
 * Constructors
 */
Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(double a, double b) {
    x = a;
    y = b;
}

bool Point::operator<(Point b) {
    if (y != b.y)
        return y < b.y;
    return x < b.x;
}

bool operator==(Point &a, Point &b) {
    return (a.x == b.x && a.y == b.y);
}

bool operator!=(Point &a, Point &b) {
	return (a.x != b.x || a.y != b.y);
}