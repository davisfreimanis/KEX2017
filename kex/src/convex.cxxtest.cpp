#include <cxxtest/TestSuite.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <stack>

#include "../src/point.h"
#include "../src/orthant_scan.h"
#include "../src/graham_scan.h"

using namespace std;

class MyTestSuite : public CxxTest::TestSuite {
public:
	void testPointDefaultConstructor() {
		Point a;
		TS_ASSERT_EQUALS(a.x, 0);
		TS_ASSERT_EQUALS(a.y, 0);
	}

	void testPointConstructorTwoParameters() {
		Point a(1, 2);
		TS_ASSERT_EQUALS(a.x, 1);
		TS_ASSERT_EQUALS(a.y, 2);
	}

	void testPointEquals() {
		Point a(1, 2);
		Point b(1, 2);
		Point c(2, 2);
		TS_ASSERT_EQUALS(a == b, true);
		TS_ASSERT_EQUALS(a == c, false);
	}

	void testPointInTriangle() {
		Point x(0, 0);
		Point y(1, 0);
		Point z(0, 1);
		Point a(0.3, 0.3);
		Point b(1, 1);
		Point c(0, 0.4);
		TS_ASSERT_EQUALS(pointInTriangle(x, y, z, a), true);
		TS_ASSERT_EQUALS(pointInTriangle(x, y, z, b), false);
		TS_ASSERT_EQUALS(pointInTriangle(x, y, z, c), false);
	}

	void testFindCenter() {
		int n = 10;
		vector <Point> v; // input points
		v.reserve(n);

		Point center(0, 0);
		Point x(0, 0);
		Point y(1, 1);
		Point z(2, 2);
		Point h(3, -1);

		v.push_back(x);
		v.push_back(y);
		v.push_back(z);
		v.push_back(h);

		center = findCenter(&v[0], v.size(), center);
		TS_ASSERT_EQUALS(center.x, 1.5);
		TS_ASSERT_EQUALS(center.y, 0.5);
	}

	void testGrahamScan() {
		vector<Point> points;
		points.reserve(10);
		Point a(0,0);
		Point b(1,1);
		Point c(2,2);
		Point d(3,-1);

		points.push_back(a);
		points.push_back(b);
		points.push_back(c);
		points.push_back(d);

		stack<Point> hull = grahamScan(&points[0], points.size());

		Point p = hull.top();
		TS_ASSERT_EQUALS(p.x, 0);
		TS_ASSERT_EQUALS(p.y, 0);
		hull.pop();
		p = hull.top();
		TS_ASSERT_EQUALS(p.x, 2);
		TS_ASSERT_EQUALS(p.y, 2);
		hull.pop();
		p = hull.top();
		TS_ASSERT_EQUALS(p.x, 3);
		TS_ASSERT_EQUALS(p.y, -1);
		hull.pop();
	}

	void testGrahamScanKattis() {
		vector<Point> points;
		points.reserve(10);
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

		stack<Point> hull = grahamScan(&points[0], points.size());

		Point p = hull.top();
		TS_ASSERT_EQUALS(p.x, -51);
		TS_ASSERT_EQUALS(p.y, -6);
		hull.pop();
		p = hull.top();
		TS_ASSERT_EQUALS(p.x, 73);
		TS_ASSERT_EQUALS(p.y, 17);
		hull.pop();
		p = hull.top();
		TS_ASSERT_EQUALS(p.x, -24);
		TS_ASSERT_EQUALS(p.y, -74);
		hull.pop();
	}

	void testGrahamScanEqual() {
		vector<Point> points;
		points.reserve(10);
		Point a(50,50);
		Point b(50,50);

		points.push_back(a);
		points.push_back(b);

		stack<Point> hull = grahamScan(&points[0], points.size());

		TS_ASSERT_EQUALS(hull.size(), 1);
	}
};