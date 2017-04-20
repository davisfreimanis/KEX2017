#include <cxxtest/TestSuite.h>
#include <sstream>
#include <iostream>
#include <vector>

#include "../src/point.h"
#include "../src/orthant_scan.h"

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
};