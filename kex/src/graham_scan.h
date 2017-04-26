#include <cstdio>
#include <vector>
#include <algorithm>
#include "point.h"

using namespace std;

#ifndef KEX2017_GRAHAMS_SCAN_H
#define KEX2017_GRAHAMS_SCAN_H

// returns -1 if a -> b -> c forms a counter-clockwise turn,
// +1 for a clockwise turn, 0 if they are collinear
double ccw(Point a, Point b, Point c);
// returns square of Euclidean distance between two points
double sqrDist(Point a, Point b);
// used for sorting points according to polar order w.r.t the pivot
bool POLAR_ORDER(Point a, Point b);
void grahamScan(vector<Point> &points, vector<Point> &bp);

#endif //KEX2017_GRAHAMS_SCAN_H
