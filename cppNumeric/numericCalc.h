#pragma once

#include <vector>
#include <iostream>

struct point { double x, y; };

class numericCalc
{
private:
	std::vector<point> dataPoints;
	double derivX;
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
	void setDerivativeSearchPoint(double val) { derivX = val; }
	double getDerivativeSearchPoint() { return derivX; }
	virtual double getNumericValue() = 0;
};

class ncRightRects:public numericCalc
{
public:
	double getNumericValue() override;
	ncRightRects() {};
};

class ncTrapezoid :public numericCalc
{
public:
	double getNumericValue() override;
	ncTrapezoid() {};
};

class ncSimpson :public numericCalc
{
public:
	double getNumericValue() override;
	ncSimpson() {};
};

class ncDerivative :public numericCalc
{
private:
	double(*baseFunc)(double, double, double, double);
	double derivPrecision;
public:
	double getNumericValue() override;
	ncDerivative() { setDerivativeSearchPoint(0); };
	ncDerivative(double dsp) { setDerivativeSearchPoint(dsp); };
	void setBaseFunc(double(*bf)(double, double, double, double))
	{
		baseFunc = bf;
	}
	void setDerivPrecision(double val) { derivPrecision = val; }
	double getDerivPrecision() { return derivPrecision; }
	double getDerivativeByFunction(double a, double b, double c);
};

class ncBasicMin :public numericCalc
{
public:
	double getNumericValue() override;
	ncBasicMin() {};
};

class ncGoldenDiv :public numericCalc
{
private:
	double(*baseFunc)(double, double, double, double);
	double prec;
	double x1, x2;
	double a, b, c;
	point minPt;
public:
	void printMyState(double ap, double bp, double gx1, double gx2, double y1, double y2, double min);
	double getNumericValue() override;
	ncGoldenDiv() { setPrecision(0.0001); };
	void setBaseFunc(double(*bf)(double, double, double, double))
	{
		baseFunc = bf;
	}
	void setPrecision(double val) { prec = val; }
	double getPrecision() { return prec; }
	void setDiapason(double dx1, double dx2)
	{
		x1 = dx1; x2 = dx2;
	}
	double getX1() { return x1; }
	double getX2() { return x2; }
	void setFuncCoeffs(double ca, double cb, double cc)
	{
		a = ca; b = cb; c = cc;
	};
};