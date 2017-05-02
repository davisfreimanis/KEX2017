#include <sstream>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

#include "point.h"
#include "orthant_scan.h"
#include "graham_scan.h"

using namespace std;

int main() {
	cout << "ORTHANT SCAN" << endl;

	int n;
	double x;
	double y;
	while(cin >> n) {
		if(n == 0) {
			cout << "No points" << endl;
			break;
		}
		vector<Point> points;
		points.reserve(n);
		for (int i = 0; i < n; ++i) {
			cin >> x >> y;
			points.push_back(Point(x,y));
		}

		orthantScan(points);
		//vector<Point> bp;
		//grahamScan(points, bp);
		//cout << bp.size() << endl;

		// remove duplicate points
		// sort(points.begin(), points.end());
		// points.erase(unique(points.begin(), points.end()), points.end());
	}

	/*
	Point a(41,-6);
	Point b(-24,-74);
	Point c(-51,-6);
	Point d(73,17);
	Point e(-30,-34);

	points.push_back(a);
	points.push_back(b);
	points.push_back(c);
	points.push_back(d);
	points.push_back(e);
	*/



    return 0;
}

