#include "point.h"
#include "orthant_scan.h"
#include "graham_scan.h"
#include <ctime>
#include <chrono>
#include <fstream>
#include <cmath> // abs
#include <limits> // epsilon
#include "omp.h"

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
	for(auto &p : points) {
		p.x -= dx;
		p.y -= dy;
	}
	for(auto &p : bp) {
		p.x -= dx;
		p.y -= dy;
	}
}

/*
 * Partitions the points in 4 vectors corresponding to each vector
 */
void quadrantPartition(vector<Point> &p1, vector<Point> &p2, vector<Point> &p3, vector<Point> &p4, vector<Point> &points) {
	for (auto p : points) {
		if(p.x >= 0 && p.y >= 0) { // Q1
			p1.push_back(p);
		} else if(p.x < 0 && p.y > 0) { // Q2
			p2.push_back(p);
		} else if(p.x <= 0 && p.y <= 0) { // Q3
			p3.push_back(p);
		} else if(p.x > 0 && p.y < 0) { // Q4
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
		// first point
		if(!eucl) {
			curX = p;
			curY = p;
			curEucl.push_back(p);
			eucl = true;
			x = false;
			y = false;

		// If the euclidian distance is the same as the current max euclidian distance point
		} else if( abs(((pow(p.x, 2) + pow(p.y, 2)) - (pow(curEucl[0].x, 2) + pow(curEucl[0].y, 2)))) < 0.0001/*numeric_limits<double>::epsilon()*/ ) {
		//} else if(((pow(p.x, 2) + pow(p.y, 2)) == (pow(curEucl[0].x, 2) + pow(curEucl[0].y, 2)) )) {
			// if point higher x coordinate
			if(pow(p.x,2) >= pow(curX.x, 2)) {
				curX = p;
				x = false;
			}
			// if point higher y coordinate
			if(pow(p.y,2) >= pow(curY.y, 2)) {
				curY = p;
				y = false;
			}
			curEucl.push_back(p);
			eucl = true;
		// If larger euclidian distance
		} else if( ((pow(p.x, 2) + pow(p.y, 2)) > (pow(curEucl[0].x, 2) + pow(curEucl[0].y, 2)) )) {
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
		// Check larger x coordinate
		} else if(pow(p.x, 2) > pow(curX.x, 2) || ((pow(p.x, 2) == pow(curX.x, 2) && pow(p.y, 2) > pow(curX.y, 2)) )) {
			curX = p;
			x = true;
		// Check larger y coordinate
		} else if(pow(p.y, 2) > pow(curY.y, 2) || ((pow(p.y, 2) == pow(curX.y, 2) && pow(p.x, 2) > pow(curX.x, 2)) )) {
			curY = p;
			y = true;
		}
	}

	if(x || curX.x > curEucl[0].x) {
		ep.push_back(curX);
	}

	if(y || curY.y > curEucl[0].y) {
		ep.push_back(curY);
	}

	if(eucl) {
		for(auto p : curEucl) {
			ep.push_back(p);
		}
	}
}

/*
 * Calls quadrantPartitionHelper for each quadrant to populate quadrant vectors
 */
void maxOrthantPoints(vector<Point> &p1, vector<Point> &p2, vector<Point> &p3, vector<Point> &p4, vector<Point> &ep) {
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			if(p1.size() > 0) {
				maxOrthantPointsHelper(p1, ep);
			}
		}

		#pragma omp section
		{
			if (p2.size() > 0) {
				maxOrthantPointsHelper(p2, ep);
			}
		}

		#pragma omp section
		{
			if (p3.size() > 0) {
				maxOrthantPointsHelper(p3, ep);
			}
		}

		#pragma omp section
		{
			if (p4.size() > 0) {
				maxOrthantPointsHelper(p4, ep);
			}
		}
	}
	//#pragma omp barrier
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

void findOuter(vector<Point> &points, vector<Point> &bp, vector<Point> &ip) {
	Point first = bp[0];
	Point last = bp[bp.size()-1];

	for (int k = 0; k < points.size(); k++) {
		bool found = false;
		for (unsigned int i = 0; i < bp.size() - 1; i++) {
			if (pointInTriangle(Point(0, 0), bp[i], bp[i + 1], points[k])) {
				found = true;
				break;
			}
		}
		if (!found && pointInTriangle(Point(0, 0), first, last, points[k])) {
			found = true;
		}
		// point not in convex polygon. Add to outer points ip
		if (!found) {
			double xt = points[k].x;
			double yt = points[k].y;
			Point temp(xt, yt);
			ip.push_back(temp);
		}
	}
}

void findOuterPara(vector<Point> &points, vector<Point> &bp, vector<Point> &ip) {
	Point first = bp[0];
	Point last = bp[bp.size()-1];

	#pragma omp parallel for
	for (int k = 0; k < points.size(); k++) {
		bool found = false;
		for (unsigned int i = 0; i < bp.size() - 1; i++) {
			if (pointInTriangle(Point(0, 0), bp[i], bp[i + 1], points[k])) {
				found = true;
				break;
			}
		}
		if (!found && pointInTriangle(Point(0, 0), first, last, points[k])) {
			found = true;
		}
		// point not in convex polygon. Add to outer points ip
		if (!found) {
			double xt = points[k].x;
			double yt = points[k].y;
			Point temp(xt, yt);
			#pragma omp critical
			ip.push_back(temp);
		}
	}
}

vector<Point> orthantScan(vector<Point> &points) {
	typedef std::chrono::high_resolution_clock Clock;
	auto t1 = Clock::now();
	auto t2 = Clock::now();
	bool debug = false;
	int iterations = 0;
	auto totalOrtantPoints = 0;
	auto totalFindOuter = 0;

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

		t1 = Clock::now();
		findCenter(points, bp, center);
		t2 = Clock::now();
		if(debug) {
			std::cout << "FindCenter: "
					  << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
					<< " ms" << std::endl;
		}

		double dx = center.x - oldCenter.x;
		double dy = center.y - oldCenter.y;

		t1 = Clock::now();
		adjustCoordinates(points, bp, dx, dy);
		t2 = Clock::now();
		if(debug) {
			std::cout << "AdjustCoordinates: "
					  << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
					<< " ms" << std::endl;
		}

		t1 = Clock::now();
		quadrantPartition(p1, p2, p3, p4, points);
		t2 = Clock::now();
		if(debug) {
			std::cout << "QuadrantPartition: "
					  << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
					<< " ms" << std::endl;
		}

		t1 = Clock::now();
		maxOrthantPoints(p1, p2, p3, p4, ep);
		t2 = Clock::now();
		if(debug) {
			std::cout << "MaxOrthantPoints: "
					  << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
					<< " ms" << std::endl;
		}
		totalOrtantPoints += chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

		t1 = Clock::now();
		ep.insert(ep.end(), bp.begin(), bp.end());
		bp.clear();

		grahamScan(ep, bp);

		t2 = Clock::now();
		if(debug) {
			std::cout << "GrahamScan: "
					  << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
					<< " ms" << std::endl;
		}

		//cout << "Points: " << points.size() << " Border: " << bp.size() << " Outer: " << ip.size() << endl;
		//sort(points.begin(), points.end());

		t1 = Clock::now();
		findOuterPara(points, bp, ip);
		t2 = Clock::now();
		if(debug) {
			std::cout << "FindOuter: "
					  << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
					<< " ms" << std::endl;
		}
		totalFindOuter += chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

		//sort(ip.begin(), ip.end());

		//cout << "OUTER points: " << ip.size() << endl;

		t1 = Clock::now();
		points.swap(ip);
		t2 = Clock::now();
		if(debug) {
			std::cout << "PointSwap: "
					  << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
					  << " ms" << std::endl;
		}

		ip.clear();
		ep.clear();
		p1.clear();
		p2.clear();
		p3.clear();
		p4.clear();

		iterations++;
	}


	cout << "Size: " << bp.size() << endl;
	cout << "Number of iterations: " << iterations << endl;
	cout << "Total time maxOrthantPoints: " << totalOrtantPoints << "ms" << endl;
	cout << "Total time findOuter: " << totalFindOuter << "ms" << endl;

	cout << "Average time maxOrthantPoints: " << totalOrtantPoints/iterations << "ms" << endl;
	cout << "Average time findOuter: " << totalFindOuter/iterations << "ms" << endl;


	ofstream poi;
	poi.open("hull1.dat");
	for(auto p : bp) {
		poi << p.x << " " << p.y << endl;
	}
	poi.close();
	return bp;
}