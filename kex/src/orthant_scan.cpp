#include "point.h"
#include "orthant_scan.h"
#include "graham_scan.h"
#include <iostream> // std::cout, std::endl
#include <vector> // std::vector
#include <algorithm> // std::sort, std::set_intersection
#include <math.h>

using namespace std;

/*
 * Returns the center of all the points.
 */
void findCenter(vector<Point> &points, vector<Point> &bp, Point &center) {
    double x = 0;
    double y = 0;

	int size = points.size() + bp.size();

    for (auto p : points) {
        x += p.x;
        y += p.y;
    }
	for(auto p : bp) {
		x += p.x;
		y += p.y;
	}

    center.x = x/size;
    center.y = y/size;
}

/*
 * Adjusts all the coordinates to the new centroid
 */
void adjustCoordinates(vector<Point> &points, vector<Point> &bp, double dx, double dy) {
	for(auto p : points) {
		p.x -= dx;
		p.y -= dy;
	}
	for(auto p : bp) {
		p.x -= dx;
		p.y -= dy;
	}
}

/*
 * Partitions the points in 4 vectors corresponding to each vector
 */
void quadrantPartition(vector<Point> &p1, vector<Point> &p2, vector<Point> &p3, vector<Point> &p4, vector<Point> &points, Point c) {
	for (auto p : points) {
		if(p.x >= c.x && p.y >= c.y) { // Q1
			p1.push_back(p);
		} else if(p.x < c.x && p.y > c.y) { // Q2
			p2.push_back(p);
		} else if(p.x <= c.x && p.y <= c.y) { // Q3
			p3.push_back(p);
		} else if(p.x > c.x && p.y < c.y) { // Q4
			p4.push_back(p);
		}
	}
}

/*
 * Adds extreme points in quadrant to vector
 */
void maxOrthantPointsHelper(vector<Point> &points, vector<Point> &ep) {
	Point curX(0,0);
	Point curY(0,0);
	vector<Point> curEucl;
	bool x = false;
	bool y = false;
	bool eucl = false;

	for(auto p : points) {

		if(!eucl || (pow(p.x, 2) + pow(p.y, 2) == pow(curEucl[0].x, 2) + pow(curEucl[0].y, 2))) {
			if(pow(p.x,2) >= pow(curX.x, 2)) {
				curX = p;
				x = false;
			}
			if(pow(p.y,2) >= pow(curY.y, 2)) {
				curY = p;
				y = false;
			}

			curEucl.push_back(p);
			eucl = true;
		} else if(!eucl || (pow(p.x, 2) + pow(p.y, 2) > pow(curEucl[0].x, 2) + pow(curEucl[0].y, 2))) {
			if(pow(p.x,2) >= pow(curX.x, 2)) {
				curX = p;
				x = false;
			}
			if(pow(p.y,2) >= pow(curY.y, 2)) {
				curY = p;
				y = false;
			}

			curEucl.clear();
			curEucl.push_back(p);
			eucl = true;
		} else if(pow(p.x, 2) > pow(curX.x, 2) || (pow(p.x, 2) == pow(curX.x, 2) && pow(p.y, 2) > pow(curX.y, 2))) {
			curX = p;
			x = true;
		} else if(pow(p.y, 2) > pow(curX.y, 2) || (pow(p.y, 2) == pow(curX.y, 2) && pow(p.x, 2) > pow(curX.x, 2))) {
			curY = p;
			y = true;
		}
	}

	if(x) {
		cout << "(" << curX.x << ") pushed back max X" << endl;
		ep.push_back(curX);
	}

	if(y) {
		cout << "(" << curY.x << ") pushed back max Y" << endl;
		ep.push_back(curY);
	}

	if(eucl) {
		for(auto p : curEucl) {
			cout << "(" << p.x << ") pushed back max eucl" << endl;
			ep.push_back(p);
		}
	}
}

/*
 * Calls quadrantPartitionHelper for each quadrant to populate quadrant vectors
 */
void maxOrthantPoints(vector<Point> &p1, vector<Point> &p2, vector<Point> &p3, vector<Point> &p4, vector<Point> &ep) {
	if(p1.size() > 0) {
		cout << "P1: " << p1.size() << endl;
		for(auto p : p1) {
			cout << p.x << " " << p.y << endl;
		}
		maxOrthantPointsHelper(p1, ep);
	}
	if(p2.size() > 0) {
		cout << "P2: " << p2.size() << endl;
		for(auto p : p2) {
			cout << p.x << " " << p.y << endl;
		}
		maxOrthantPointsHelper(p2, ep);
	}
	if(p3.size() > 0) {
		cout << "P3: " << p3.size() << endl;
		for(auto p : p3) {
			cout << p.x << " " << p.y << endl;
		}
		maxOrthantPointsHelper(p3, ep);
	}
	if(p4.size() > 0) {
		cout << "P4: " << p4.size() << endl;
		for(auto p : p4) {
			cout << p.x << " " << p.y << endl;
		}
		maxOrthantPointsHelper(p4, ep);
	}
}

/*
 * Checks if point p is inside triangle made of a, b and c
 * http://stackoverflow.com/a/14382692
 * True if point in triangle, False otherwise
 */
bool pointInTriangle(Point a, Point b, Point c, Point p) {
	double area = 0.5 * (-b.y*c.x + a.y*(-b.x + c.x) + a.x * (b.y - c.y) + b.x * c.y);
	double s = 1 / (2 * area) * (a.y*c.x - a.x * c.y + (c.y - a.y) * p.x + (a.x - c.x) * p.y);
	double t = 1 / (2 * area) * (a.x*b.y - a.y * b.x + (a.y - b.y) * p.x + (b.x - a.x) * p.y);

	return s >= 0 && t >= 0 && 1-s-t >= 0;
}

void findInterior(Point center, vector<Point> &points, vector<Point> &bp, vector<Point> &ip) {
	Point first = bp[0];
	Point last = bp[bp.size()-1];
	bool found = false;

	for(auto p : points) {
		found = false;
		for(int i = 0; i < bp.size()-1; i++) {
			if(pointInTriangle(center, bp[i], bp[i+1], p)) {
				ip.push_back(p);
				found = true;
				break;
			}
		}
		if(!found && pointInTriangle(center, first, last, p)) {
			ip.push_back(p);
			continue;
		}
	}
}

/*
 * Calculates the final set of points after the round
 * p <- p - bp - ip
 */
void pointSetSubtraction(vector<Point> &points, vector<Point> &bp, vector<Point> &ip) {
	vector<Point> res;

	sort(points.begin(), points.end());
	sort(bp.begin(), bp.end());

	// res <- p - bp
	std::set_difference(points.begin(), points.end(), bp.begin(), bp.end(),
						std::inserter(res, res.end()));

	sort(res.begin(), res.end());
	sort(ip.begin(), ip.end());
	points.clear();

	// p <- res - ip
	std::set_difference(res.begin(), res.end(), ip.begin(), ip.end(),
						std::inserter(points, points.end()));

	//bp.clear();
	ip.clear();
}

void orthantScan(vector<Point> &points) {
	vector<Point> bp;
	vector<Point> ep;
	vector<Point> ip;

	vector<Point> p1;
	vector<Point> p2;
	vector<Point> p3;
	vector<Point> p4;

	Point center(0,0);

	while (points.size() > 0) {
		Point oldCenter = center;
		findCenter(points, bp, center);

		double dx = center.x - oldCenter.x;
		double dy = center.y - oldCenter.y;

		adjustCoordinates(points, bp, dx, dy);
		quadrantPartition(p1, p2, p3, p4, points, center);
		maxOrthantPoints(p1, p2, p3, p4, ep);
		cout << "*****************Extreme: " << ep.size() << endl;

		for(auto p : ep) {
			cout << p.x << " " << p.y << endl;
		}
		grahamScan(points, bp);
		cout << "*****************Border: " << bp.size() << endl;

		for(auto p : bp) {
			cout << p.x << " " << p.y << endl;
		}

		findInterior(center, points, bp, ip);
		cout << "******************Interior: " << ip.size() << endl;

		for(auto p : ip) {
			cout << p.x << " " << p.y << endl;
		}

		pointSetSubtraction(points, bp, ip);
		cout << "*******************Points " << points.size() << endl;

		for(auto p : points) {
			cout << p.x << " " << p.y << endl;
		}
	}


	cout << "***************FINAL size: " << bp.size() << endl;
	for(auto p : bp) {
		cout << p.x << " " << p.y << endl;
	}
}