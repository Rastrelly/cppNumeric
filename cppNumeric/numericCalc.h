#pragma once

#include <vector>

struct point { double x, y; };

class numericCalc
{
private:
	std::vector<point> dataPoints;
public:
	numericCalc() {};
	void assignVector(std::vector<point> inpVector)
	{
		dataPoints = inpVector;
	}
	void addDataPoint(point dp) { dataPoints.push_back(dp); }
	void clearDataPoints() { dataPoints.clear(); }
	int getDPSize() { return dataPoints.size(); }
	point getDataPoint(int id) { return dataPoints[id]; }
	virtual double getIntegral() = 0;
};

class ncRightRects:public numericCalc
{
public:
	double getIntegral() override;
	ncRightRects() {};
};

