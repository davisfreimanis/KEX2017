#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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

	quadrantPartition(p1, p2, p3, p4, points, center);
	maxOrthantPoints(p1, p2, p3, p4, ep);

	ofstream poi;
	poi.open("points.dat");
	for(auto p : points) {
		poi << p.x << " " << p.y << endl;
	}

	poi.close();

	ofstream extreme;
	extreme.open("extreme.dat");

	for(auto p : ep) {
		extreme << p.x << " " << p.y << endl;
	}

	extreme.close();
	grahamScan(ep, bp);
	Point end = bp.front();
	bp.push_back(end);
	findOuter(center, points, bp, ip);
	cout << "IP SIZe: " << ip.size() << ip[0].x << endl;
	ofstream fhull;
	fhull.open("fhull.dat");

	for(auto p : bp) {
		fhull << p.x << " " << p.y << endl;
	}

	fhull.close();

	ofstream outer;
	outer.open("outer.dat");

	for(auto p : ip) {
		outer << p.x << " " << p.y << endl;
	}

	outer.close();


	bp.clear();
	grahamScan(points, bp);
	end = bp.front();
	bp.push_back(end);

	ofstream hull;
	hull.open("hull.dat");

	for(auto p : bp) {
		hull << p.x << " " << p.y << endl;
	}
	hull.close();
}

int main() {
	vector<Point> points;
	vector<Point> bp;


	readInput(points);
	//generateData(points);

	orthantScan(points);
	//grahamScan(points, bp);

    return 0;
}

