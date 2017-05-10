#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
#include "point.h"
#include "orthant_scan.h"
#include "graham_scan.h"

using namespace std;

void readInput(vector<Point> &points) {
	int n;
	double x;
	double y;
	string skit;
	getline(cin, skit);
	while(cin >> n) {
		if(n == 0) {
			cout << "No points" << endl;
			break;
		}
		points.reserve(n);
		for (int i = 0; i < n; ++i) {
			cin >> x >> y;
			points.push_back(Point(x,y));
		}
	}
}

void generateData(vector<Point> &points) {
	vector<Point> bp;
	vector<Point> ep;
	vector<Point> ip;

	vector<Point> p1;
	vector<Point> p2;
	vector<Point> p3;
	vector<Point> p4;

	Point center(0,0);

	grahamScan(points, bp);

	ofstream hull;
	hull.open("hull.dat");

	for(auto p : bp) {
		hull << p.x << " " << p.y << endl;
	}
	hull.close();


	/*
	 * ORIGINAL COORDINATES
	 */
	ofstream poi;
	poi.open("points1.dat");
	for(auto p : points) {
		poi << p.x << " " << p.y << endl;
	}
	poi.close();

	Point oldCenter = center;
	findCenter(points, bp, center);
	double dx = center.x - oldCenter.x;
	double dy = center.y - oldCenter.y;


	/*
	 * ADJUSTED COORDINATES
	 */
	adjustCoordinates(points, bp, dx, dy);
	poi.open("points2.dat");
	for(auto p : points) {
		poi << p.x << " " << p.y << endl;
	}
	poi.close();

	quadrantPartition(p1, p2, p3, p4, points);
	maxOrthantPoints(p1, p2, p3, p4, ep);

	poi.open("extreme.dat");

	for(auto p : ep) {
		poi << p.x << " " << p.y << endl;
	}

	poi.close();

	grahamScan(ep, bp);
	//Point end = bp.front();
	//bp.push_back(end);
	findOuter(points, bp, ip);
	cout << "IP SIZe: " << ip.size() << endl;
	cout << "BP SIZe: " << bp.size() << endl;

	ofstream fhull;
	fhull.open("fhull.dat");

	for(auto p : bp) {
		fhull << p.x << " " << p.y << endl;
	}

	fhull.close();

	poi.open("outer.dat");

	for(auto p : ip) {
		poi << p.x << " " << p.y << endl;
	}

	poi.close();

	points.swap(ip);

	bp.clear();

}

int main() {
	vector<Point> points;
	vector<Point> bp;

	readInput(points);
	//generateData(points);
	//plot "points2.dat" using 1:2, "extreme.dat" using 1:2 lc 7, "fhull.dat" using 1:2 lc 7 pt 7 with linespoints, "outer.dat" using 1:2 lc 6 pt 6

	typedef std::chrono::high_resolution_clock Clock;
	auto t1 = Clock::now();

	orthantScan(points);
	//grahamScan(points, bp);

	auto t2 = Clock::now();
	std::cout << "Total time: "
			  << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
			  << " ms" << std::endl;
	cout << bp.size() << endl;

    return 0;
}

