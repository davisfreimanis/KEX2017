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

vector<Point> grahamScan(Point *points, int N) {
	vector<Point> hull;

	if (N < 3) {
		return hull;
	}

	// find the point having the least y coordinate (pivot),
	// ties are broken in favor of lower x coordinate
	int leastY = 0;
	for (int i = 1; i < N; i++) {
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
	sort(points + 1, points + N, POLAR_ORDER);

	hull.push_back(points[0]);
	hull.push_back(points[1]);
	hull.push_back(points[2]);

	for (int i = 3; i < N; i++) {
		Point top = hull.back();
		hull.pop_back();
		while (ccw(hull.back(), top, points[i]) != -1) {
			top = hull.back();
			hull.pop_back();
		}
		hull.push_back(top);
		hull.push_back(points[i]);
	}
	return hull;
}