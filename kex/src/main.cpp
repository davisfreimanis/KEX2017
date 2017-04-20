#include "point.h"
#include "orthant_scan.h"
#include "graham_scan.h"
#include <iostream> // std::cout, std::endl
#include <vector> // std::vector
#include <algorithm> // std::sort, std::set_intersection

using namespace std;

int main() {

	int n;
	int x;
	int y;
	while(cin >> n) {
		if(n == 0) {
			break;
		}
		vector<Point> points;
		points.reserve(n);
		for (int i = 0; i < n; ++i) {
			cin >> x >> y;
			Point a(x,y);
			points.push_back(a);
		}

		sort(points.begin(), points.end());
		points.erase(unique(points.begin(), points.end()), points.end());

		if(points.size() < 3) {
			cout << points.size() << endl;
			for (int i = 0; i < points.size(); ++i) {
				cout << points[i].x << " " << points[i].y << endl;
			}
		} else {
			stack<Point> hull = grahamScan(&points[0], points.size());
			cout << hull.size() << endl;
			while (!hull.empty()) {
				Point p = hull.top();
				hull.pop();
				cout << p.x << " " << p.y << endl;
			}
		}

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

