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

	void testPointInTriangleBoundries() {
		Point a(0,0);
		Point b(2,0);
		Point c(2,2);

		Point x(1,0); // on edge
		Point y(1,0); // on edge
		Point z(2,0); // on corner

		TS_ASSERT_EQUALS(pointInTriangle(a, b, c, x), false); // ccw
		TS_ASSERT_EQUALS(pointInTriangle(a, c, b, y), false); // cw
		TS_ASSERT_EQUALS(pointInTriangle(a, b, c, z), false); // corner
		TS_ASSERT_EQUALS(pointInTriangle(a, c, b, z), false); // corner
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

		center = findCenter(v, center);
		TS_ASSERT_EQUALS(center.x, 1.5);
		TS_ASSERT_EQUALS(center.y, 0.5);
	}

	void testQuadrantPartition() {
		int n = 10;
		vector <Point> v; // input points
		v.reserve(n);

		vector<Point> p1;
		vector<Point> p2;
		vector<Point> p3;
		vector<Point> p4;

		Point center(0, 0);
		Point x(0, 0);
		Point y(1, 1);
		Point z(2, 2);
		Point h(3, -1);

		v.push_back(x);
		v.push_back(y);
		v.push_back(z);
		v.push_back(h);

		center = findCenter(v, center);

		quadrantPartition(p1, p2, p3, p4, v, center);

		TS_ASSERT_EQUALS(p1.size(), 1);
		TS_ASSERT_EQUALS(p2.size(), 1);
		TS_ASSERT_EQUALS(p3.size(), 1);
		TS_ASSERT_EQUALS(p4.size(), 1);
	}

	void testMaxQuadrantPoints() {
		int n = 10;
		vector <Point> v; // input points
		v.reserve(n);

		vector<Point> p1;
		vector<Point> p2;
		vector<Point> p3;
		vector<Point> p4;
		vector<Point> ep;

		Point center(0, 0);
		Point x(0, 0);
		Point y(1, 1);
		Point z(2, 2);
		Point h(3, -1);

		v.push_back(x);
		v.push_back(y);
		v.push_back(z);
		v.push_back(h);

		center = findCenter(v, center);

		quadrantPartition(p1, p2, p3, p4, v, center);

		maxOrthantPoints(p1, p2, p3, p4, ep);

		TS_ASSERT_EQUALS(p1[0], z);
		TS_ASSERT_EQUALS(p2[0], y);
		TS_ASSERT_EQUALS(p3[0], x);
		TS_ASSERT_EQUALS(p4[0], h);

		TS_ASSERT_EQUALS(ep.size(), 4);
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

		vector<Point> hull = grahamScan(&points[0], points.size());

		Point p = hull.back();
		TS_ASSERT_EQUALS(p.x, 0);
		TS_ASSERT_EQUALS(p.y, 0);
		hull.pop_back();
		p = hull.back();
		TS_ASSERT_EQUALS(p.x, 2);
		TS_ASSERT_EQUALS(p.y, 2);
		hull.pop_back();
		p = hull.back();
		TS_ASSERT_EQUALS(p.x, 3);
		TS_ASSERT_EQUALS(p.y, -1);
		hull.pop_back();
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

		vector<Point> hull = grahamScan(&points[0], points.size());

		Point p = hull.back();
		TS_ASSERT_EQUALS(p.x, -51);
		TS_ASSERT_EQUALS(p.y, -6);
		hull.pop_back();
		p = hull.back();
		TS_ASSERT_EQUALS(p.x, 73);
		TS_ASSERT_EQUALS(p.y, 17);
		hull.pop_back();
		p = hull.back();
		TS_ASSERT_EQUALS(p.x, -24);
		TS_ASSERT_EQUALS(p.y, -74);
		hull.pop_back();
	}

};