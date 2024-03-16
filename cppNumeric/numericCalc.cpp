#include "numericCalc.h"

double ncRightRects::getNumericValue()
{
	//get integral value via right rectangle method
	int l = getDPSize();
	double totSum = 0;
	for (int i = 0; i < l - 1; i++)
	{
		point cPoint1 = getDataPoint(i);
		point cPoint2 = getDataPoint(i + 1);
		double dx = abs(cPoint2.x - cPoint1.x);
		double dy = cPoint1.y;
		double s = dx * dy;
		totSum += s;
	}
	clearDataPoints();
	return totSum;
}

double ncTrapezoid::getNumericValue()
{
	//get integral value via trapezoid method
	int l = getDPSize();
	double totSum = 0;
	for (int i = 0; i < l - 1; i++)
	{
		point cPoint1 = getDataPoint(i);
		point cPoint2 = getDataPoint(i + 1);
		//calc for rectangle
		double x1 = cPoint1.x;
		double x2 = cPoint2.x;
		double y1 = cPoint1.y;
		double y2 = cPoint2.y;
		double s = ((y1 + y2)/2)*(x2-x1);
		//calc for triangle
		totSum += s;
	}
	clearDataPoints();
	return totSum;
}


double ncSimpson::getNumericValue()
{
	//get integral value via Simpson method
	int l = getDPSize();
	bool divBy3=true;
	if (l % 3 == 0) divBy3 = false;
	int stop = 0;
	divBy3 ? stop = 2 : stop = 3;

	double totSum = 0;
	for (int i = 0; i < l - stop; i+=2)
	{
		point cPoint1 = getDataPoint(i);
		point cPoint2 = getDataPoint(i + 1);
		point cPoint3 = getDataPoint(i + 2);
		
		double x1 = cPoint1.x;
		double x2 = cPoint2.x;
		double x3 = cPoint3.x;
		double y1 = cPoint1.y;
		double y2 = cPoint2.y;
		double y3 = cPoint3.y;

		double s = ((x3 - x1) / 6)*(y1 + 4 * y2 + y3);
		
		totSum += s;
	}

	if (!divBy3) 
	{
		point cPoint1 = getDataPoint(l-1);
		point cPoint2 = getDataPoint(l-2);

		double x1 = cPoint1.x;
		double x2 = cPoint2.x;
		double y1 = cPoint1.y;
		double y2 = cPoint2.y;

		totSum += ((y1 + y2) / 2)*(x2 - x1);
	}
	clearDataPoints();
	return totSum;
}


double ncDerivative::getNumericValue()
{
	//1. get nearest data point
	int l = getDPSize();
	double minDist = abs(getDerivativeSearchPoint() - getDataPoint(0).x);
	int minDistId = 0;
	for (int i = 0; i < l - 1; i++)
	{
		double cv = abs(getDerivativeSearchPoint() - getDataPoint(i).x);
		if (cv < minDist) { minDist = cv; minDistId = i; }
	}

	//2. get derivative value
	point p1 = getDataPoint(minDistId);
	point p2 = getDataPoint(minDistId+1);

	std::cout << "minDistId = " << minDistId << "\n";
	std::cout << "p1 = " << p1.x << "; " << p1.y << "\n";
	std::cout << "p2 = " << p2.x << "; " << p2.y << "\n";

	//3. return derivative
	clearDataPoints();
	return (p2.y - p1.y) / (p2.x - p1.x);
}

double ncDerivative::getDerivativeByFunction(double a, double b, double c)
{
	double x1 = getDerivativeSearchPoint();
	double x2 = x1 + getDerivPrecision();
	double y1 = baseFunc(a, b, c, x1);
	double y2 = baseFunc(a, b, c, x2);
	return (y2 - y1) / (x2 - x1);
}