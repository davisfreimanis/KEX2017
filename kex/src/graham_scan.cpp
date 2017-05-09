#include <cstdio>
#include <vector>
#include <algorithm>
#include "point.h"
#include "graham_scan.h"

using namespace std;

// Point having the least y coordinate, used for sorting other points
// according to polar angle about this point
Point pivot;

// returns -1 if a -> b -> c forms a counter-clockwise turn,
// +1 for a clockwise turn, 0 if they are collinear
double ccw(Point a, Point b, Point c) {
	double area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	if (area > 0)
		return -1;
	else if (area < 0)
		return 1;
	return 0;
}

// returns square of Euclidean distance between two points
double sqrDist(Point a, Point b) {
	double dx = a.x - b.x, dy = a.y - b.y;
	return dx * dx + dy * dy;
}

// used for sorting points according to polar order w.r.t the pivot
bool POLAR_ORDER(Point a, Point b) {
	double order = ccw(pivot, a, b);
	if (order == 0)
		return sqrDist(pivot, a) < sqrDist(pivot, b);
	return (order == -1);
}

void grahamScan(vector<Point> &points, vector<Point> &bp) {
	if (points.size() < 3) {
		//TODO add only points to bp

		return;
	}

	// find the point having the least y coordinate (pivot),
	// ties are broken in favor of lower x coordinate
	int leastY = 0;
	for (unsigned int i = 1; i < points.size(); i++) {
		if (points[i] < points[leastY]) {
			leastY = i;
		}
	}

	// swap the pivot with the first point
	Point temp = points[0];
	points[0] = points[leastY];
	points[leastY] = temp;

	// sort the remaining point according to polar order about the pivot
	pivot = points[0];
	sort(points.begin()+1, points.end(), POLAR_ORDER);

	bp.push_back(points[0]);
	bp.push_back(points[1]);
	bp.push_back(points[2]);

	for (unsigned int i = 3; i < points.size(); i++) {
		Point top = bp.back();
		bp.pop_back();
		while (ccw(bp.back(), top, points[i]) != -1) {
			top = bp.back();
			bp.pop_back();
		}
		bp.push_back(top);
		bp.push_back(points[i]);
	}
	return;
}