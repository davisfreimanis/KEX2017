#include "point.h"
#include <iostream> // std::cout, std::endl
#include <vector> // std::vector
#include <algorithm> // std::sort, std::set_intersection

using namespace std;

#ifndef KEX2017_ORTHANT_SCAN_H
#define KEX2017_ORTHANT_SCAN_H

bool pointInTriangle(Point a, Point b, Point c, Point p);
Point findCenter(vector<Point> &points, Point center);
void quadrantPartition(vector<Point> &p1, vector<Point> &p2, vector<Point> &p3, vector<Point> &p4, vector<Point> &points, Point c);
void maxOrthantPoints(vector<Point> &p1, vector<Point> &p2, vector<Point> &p3, vector<Point> &p4, vector<Point> &ep);
void maxOrthantPointsHelper(vector<Point> &points, vector<Point> &ep);
void findInterior(Point center, vector<Point> &points, vector<Point> &bp, vector<Point> &ip);
void pointSetSubtraction(vector<Point> &points, vector<Point> &bp, vector<Point> &ip);

#endif //KEX2017_ORTHANT_SCAN_H