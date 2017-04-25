#include "point.h"
#include "orthant_scan.h"
#include <iostream> // std::cout, std::endl
#include <vector> // std::vector
#include <algorithm> // std::sort, std::set_intersection
#include <math.h>

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
Point findCenter(vector<Point> &points, Point center) {
    double x = 0;
    double y = 0;

	int size = points.size();

    for (auto p : points) {
        x += p.x;
        y += p.y;
    }
    center.x = x/size;
    center.y = y/size;

    return center;
}

/*
 * Adjusts all the coordinates to the new centroid
 */
void adjustCoordinates(vector<Point> &points, double dx, double dy) {
	for(auto p : points) {
		p.x += dx;
		p.y += dy;
	}
}


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

void maxOrthantPointsHelper(vector<Point> &points, vector<Point> &ep) {
	Point curX(0,0);
	Point curY(0,0);
	vector<Point> curEucl;
	bool x = false;
	bool y = false;
	bool eucl = false;

	for(auto p : points) {
		if(pow(p.x, 2) > pow(curX.x, 2) || (pow(p.x, 2) == pow(curX.x, 2) && pow(p.y, 2) > pow(curX.y, 2))) {
			curX = p;
			x = true;
		} else if(pow(p.y, 2) > pow(curX.y, 2) || (pow(p.y, 2) == pow(curX.y, 2) && pow(p.x, 2) > pow(curX.x, 2))) {
			curY = p;
			y = true;
		} else if(!eucl || (pow(p.x, 2) + pow(p.y, 2) == pow(curEucl[0].x, 2) + pow(curEucl[0].y, 2))) {
			curEucl.push_back(p);
			eucl = true;
		} else if(!eucl || (pow(p.x, 2) + pow(p.y, 2) > pow(curEucl[0].x, 2) + pow(curEucl[0].y, 2))) {
			curEucl.clear();
			curEucl.push_back(p);
			eucl = true;
		}
	}

	if(x) {
		ep.push_back(curX);
	}

	if(y) {
		ep.push_back(curY);
	}

	if(eucl) {
		for(auto p : curEucl) {
			ep.push_back(p);
		}
	}
}

void maxOrthantPoints(vector<Point> &p1, vector<Point> &p2, vector<Point> &p3, vector<Point> &p4, vector<Point> &ep) {
	if(p1.size() > 0) {
		maxOrthantPointsHelper(p1, ep);
	}
	if(p2.size() > 0) {
		maxOrthantPointsHelper(p2, ep);
	}
	if(p3.size() > 0) {
		maxOrthantPointsHelper(p3, ep);
	}
	if(p4.size() > 0) {
		maxOrthantPointsHelper(p4, ep);
	}
}

vector<Point> orthantScan(Point *Points, int size) {
    vector<Point> bp(size);
    vector<Point> ep(size);

    vector<Point> p1(size);
    vector<Point> p2(size);
    vector<Point> p3(size);
    vector<Point> p4(size);


}