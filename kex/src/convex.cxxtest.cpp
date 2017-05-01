#include <cxxtest/TestSuite.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

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
		TS_ASSERT_EQUALS(pointInTriangle(x, y, z, c), true);
	}

	void testPointInTriangleBoundries() {
		Point a(0,0);
		Point b(2,0);
		Point c(2,2);

		Point x(1,0); // on edge
		Point y(1,0); // on edge
		Point z(2,0); // on corner

		TS_ASSERT_EQUALS(pointInTriangle(a, b, c, x), true); // ccw
		TS_ASSERT_EQUALS(pointInTriangle(a, c, b, y), true); // cw
		TS_ASSERT_EQUALS(pointInTriangle(a, b, c, z), true); // corner
		TS_ASSERT_EQUALS(pointInTriangle(a, c, b, z), true); // corner
	}

	void testFindCenter() {
		int n = 10;
		vector <Point> v; // input points
		v.reserve(n);

		vector<Point> bp;

		Point center(0, 0);
		Point x(0, 0);
		Point y(1, 1);
		Point z(2, 2);
		Point h(3, -1);

		v.push_back(x);
		v.push_back(y);
		v.push_back(z);
		v.push_back(h);

		findCenter(v, bp, center);
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
		vector<Point> bp;


		Point center(0, 0);
		Point x(0, 0);
		Point y(1, 1);
		Point z(2, 2);
		Point h(3, -1);

		v.push_back(x);
		v.push_back(y);
		v.push_back(z);
		v.push_back(h);

		findCenter(v, bp, center);

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
		vector<Point> bp;

		Point center(0, 0);
		Point x(0, 0);
		Point y(1, 1);
		Point z(2, 2);
		Point h(3, -1);

		v.push_back(x);
		v.push_back(y);
		v.push_back(z);
		v.push_back(h);

		findCenter(v, bp, center);

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
		vector<Point> bp;
		points.reserve(10);
		Point a(0,0);
		Point b(1,1);
		Point c(2,2);
		Point d(3,-1);

		points.push_back(a);
		points.push_back(b);
		points.push_back(c);
		points.push_back(d);

		grahamScan(points, bp);

		Point p = bp.back();
		TS_ASSERT_EQUALS(p.x, 0);
		TS_ASSERT_EQUALS(p.y, 0);
		bp.pop_back();
		p = bp.back();
		TS_ASSERT_EQUALS(p.x, 2);
		TS_ASSERT_EQUALS(p.y, 2);
		bp.pop_back();
		p = bp.back();
		TS_ASSERT_EQUALS(p.x, 3);
		TS_ASSERT_EQUALS(p.y, -1);
		bp.pop_back();
	}

	void testGrahamScanKattis() {
		vector<Point> points;
		vector<Point> bp;
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

		grahamScan(points, bp);

		Point p = bp.back();
		TS_ASSERT_EQUALS(p.x, -51);
		TS_ASSERT_EQUALS(p.y, -6);
		bp.pop_back();
		p = bp.back();
		TS_ASSERT_EQUALS(p.x, 73);
		TS_ASSERT_EQUALS(p.y, 17);
		bp.pop_back();
		p = bp.back();
		TS_ASSERT_EQUALS(p.x, -24);
		TS_ASSERT_EQUALS(p.y, -74);
		bp.pop_back();
	}

	void testSetDifference() {
		vector<Point> bp;
		vector<Point> ip;
		vector<Point> points;

		Point a(0,-2);
		Point b(2,-1);
		Point c(3,3);
		Point d(-1,3);
		Point e(-3,0);
		Point center(0,0);

		Point f(5,5);
		Point g(1,0);
		Point h(0,1);
		Point i(-1,1);

		bp.push_back(a);
		bp.push_back(b);
		bp.push_back(c);
		bp.push_back(d);
		bp.push_back(e);

		points.push_back(a);
		points.push_back(b);
		points.push_back(c);
		points.push_back(d);
		points.push_back(e);
		points.push_back(f);
		points.push_back(g);
		points.push_back(h);
		points.push_back(i);

		findInterior(center, points, bp, ip);

		pointSetSubtraction(points, bp, ip);

		//cout << points.size() << endl;
		//for(auto p : points) {
		//	cout << p.x << " " << p.y << endl;
		//}
	}

	void testInteriorPoints() {
		vector<Point> bp;
		vector<Point> ip;
		vector<Point> points;

		Point a(0,-2);
		Point b(2,-1);
		Point c(3,3);
		Point d(-1,3);
		Point e(-3,0);
		Point center(0,0);

		Point f(5,5);
		Point g(1,0);
		Point h(0,1);
		Point i(-1,1);

		bp.push_back(a);
		bp.push_back(b);
		bp.push_back(c);
		bp.push_back(d);
		bp.push_back(e);

		points.push_back(a);
		points.push_back(b);
		points.push_back(c);
		points.push_back(d);
		points.push_back(e);
		points.push_back(f);
		points.push_back(g);
		points.push_back(h);
		points.push_back(i);

		findInterior(center, points, bp, ip);

		//cout << "__________________________" << endl;
		//cout << ip.size() << endl;
		//for(auto p : ip) {
		//	cout << p.x << " " << p.y << endl;
		//}
	}

	void testOrthantScan() {
		cout << "ORTHANT SCAN" << endl;

		vector<Point> points;

		Point a(-0.02222276248244826, -0.4979727817680433);
		Point b(-0.4285431913366012, 0.4745826469497594);
		Point c(0.3105396575392593, 0.2400179190933871);
		Point d(-0.01883958887200765, 0.3630260628303755);
		Point e(0.3790312361708201, 0.3779794437605696);
		Point f(-0.2994955874043476, 0.3776609263174803);
		Point g(0.3471817493878135, 0.08365533089605659);
		Point h(-0.00485819764887746, 0.3482682405489201);
		Point i(0.3443122672329771, -0.1437312230875075);
		Point j(0.309330780347186, -0.07758103877080702);

		/*
		-0.02222276248244826 -0.4979727817680433
		-0.4285431913366012 0.4745826469497594
		0.3790312361708201 0.3779794437605696
		0.3443122672329771 -0.1437312230875075
		*/

		points.push_back(a);
		points.push_back(b);
		points.push_back(c);
		points.push_back(d);
		points.push_back(e);
		points.push_back(f);
		points.push_back(g);
		points.push_back(h);
		points.push_back(i);
		points.push_back(j);

		orthantScan(points);
	}

};