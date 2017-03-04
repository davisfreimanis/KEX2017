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

/*
bool operator < (Point b) {
    if (y != b.y)
        return y < b.y;
    return x < b.x;
}*/
