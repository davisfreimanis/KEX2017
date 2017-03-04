#include <cstdio>
#include <random>
#include "point.h"

using namespace std;

vector<Point*> manualGenPoints(int nmbOfPoints);
vector<Point*> randomGenPoints(int nmbOfPoints);

int main(){
	int mode;
	scanf("%d", &mode);
	int nmbOfPoints;
	scanf("%d", &nmbOfPoints);

	vector<Point*> points;

	switch(mode){
		case 1:
			points = manualGenPoints(nmbOfPoints);
			break;
		case 2:
			points = randomGenPoints(nmbOfPoints);
			break;
		default:
			break;
	}

	for (int i = 0; i < nmbOfPoints; ++i) {
		printf("%lf %lf\n", points[i]->x, points[i]->y);
	}
}

vector<Point*> manualGenPoints(int nmbOfPoints){
	vector<Point*> pointVector(nmbOfPoints);
	for (int i = 0; i < nmbOfPoints; ++i)
	{
		double x,y;
		scanf("%lf %lf", &x, &y);
		pointVector[i] = (new Point(x,y));
	}

	return pointVector;
}
vector<Point*> randomGenPoints(int nmbOfPoints){
	vector<Point*> pointVector(nmbOfPoints);
	default_random_engine generator;
	normal_distribution<double> distribution(0.0,10.0);
	for (int i = 0; i < nmbOfPoints; ++i)
	{
		pointVector[i] = (new Point(distribution(generator),distribution(generator)));
	}

	return pointVector;
}