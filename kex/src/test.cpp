//#include "convex_hull.h"
#include "point.h"
#include <iostream>
#include <vector>

int main(int argc, char const *argv[])
{
	Point p1(1,2);
	Point p2(2,2);
	Point p3(3,6);
	Point p4(5,3);
	Point p5(5,5);
	Point p6(5,7);

	std::vector<Point> points {p1, p2, p3, p4, p5, p6};
	std::vector<Point> hull(6);

	std::cout << points.size() << std::endl;

	//convex_hull(points, points.size(), hull);

	return 0;
}