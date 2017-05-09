#include "point.h"
#include <iostream> // std::cout, std::endl
#include <vector> // std::vector
#include <algorithm> // std::sort, std::set_intersection

using namespace std;

#ifndef KEX2017_ORTHANT_SCAN_H
#define KEX2017_ORTHANT_SCAN_H

bool pointInTriangle(Point a, Point b, Point c, Point p);
void findCenter(vector<Point> &points, vector<Point> &bp, Point &center);
void adjustCoordinates(vector<Point> &points, vector<Point> &bp, double dx, double dy);
void quadrantPartition(vector<Point> &p1, vector<Point> &p2, vector<Point> &p3, vector<Point> &p4, vector<Point> &points);
void maxOrthantPoints(vector<Point> &p1, vector<Point> &p2, vector<Point> &p3, vector<Point> &p4, vector<Point> &ep);
void maxOrthantPointsHelper(vector<Point> &points, vector<Point> &ep);
void findOuter(vector<Point> &points, vector<Point> &bp, vector<Point> &ip);
vector<Point> orthantScan(vector<Point> &points);

#endif //KEX2017_ORTHANT_SCAN_H