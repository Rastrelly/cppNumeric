#include "numericCalc.h"

double ncRightRects::getIntegral()
{
	//get integral value via right rectangle method
	int l = getDPSize();
	double totSum = 0;
	for (int i = 0; i < l - 1; i++)
	{
		point cPoint1 = getDataPoint(i);
		point cPoint2 = getDataPoint(i + 1);
		double dx = abs(cPoint2.x - cPoint1.x);
		double dy = abs(cPoint1.y);
		double s = dx * dy;
		totSum += s;
	}
	return totSum;
}