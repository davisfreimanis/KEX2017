#include <cstdio>
#include <random>

using namespace std;

int main(){
	int mode;
	scanf("%d", &mode);
	int nmbOfPoints;
	scanf("%d", &nmbOfPoints);
	switch(mode){
		case 1:
			points = manualGenPoints(nmbOfPoints);
			break;
		case 2:
			points = randomGenPoints(nmbOfPoints)
			break;
	}

}

vector<Point> manualGenPoints(int nmbOfPoints){
	vector<Point> pointVector(nmbOfPoints);
	for (int i = 0; i < nmbOfPoints; ++i)
	{	
		double x,y;
		scanf("%d %d", &x, &y);
		pointVector.push_back(new Point(x,y));
	}

	return pointVector;
}
vector<Point> randomGenPoints(int nmbOfPoints){
	vector<Point> pointVector(nmbOfPoints);
	for (int i = 0; i < nmbOfPoints; ++i)
	{	
		default_random_engine generator;
		normal_distribution<double> distribution(0.0,10.0);
		pointVector.push_back(new Point(distribution(generator),distribution(generator)))
	}

	return pointVector;


}