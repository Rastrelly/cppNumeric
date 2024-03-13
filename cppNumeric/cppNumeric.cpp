#include <iostream>
#include "numericCalc.h"

//our function
double func(double a, double b, double c, double x)
{
	return a * pow(x, 2) + b * x + c;
}

//primary of our function
double funcIFirst(double a, double b, double c, double x)
{
	return (a * pow(x, 3))/3 + (b * pow(x,2))/2 + c*x;
}

//definite integral of our function
double funcIntegralAnalytical(double a, double b, double c, double x1, double x2)
{
	return funcIFirst(a, b, c, x2) - funcIFirst(a, b, c, x1);
}

void printCalcCompar(std::string calcType, double analyt, double numeric)
{
	double relErr = 0, absErr = 0;
	absErr = abs(analyt - numeric);
	relErr = (absErr / analyt) * 100.0f;
	std::cout << "Results for " << calcType.c_str() << ":\n";
	std::cout << "Analytical = " << analyt << "; Numeric = " << numeric << ";\n";
	std::cout << "AbsErr = " << absErr << "; RelErr = " << relErr << ";%\n";
}

int main()
{
	ncRightRects iCalcRR;
	std::cout << "Input a,b,c,x1,x2,d\n";
	double a, b, c, x1, x2, d;
	std::cin >> a >> b >> c >> x1 >> x2 >> d;

	double integAnalyt = funcIntegralAnalytical(a, b, c, x1, x2);
	double integNumeric = 0;

	//fill data vector
	std::vector<point> funcPts = {};
	double cx = x1;
	long long int n = (x2 - x1) / d;
	long long int i = 0, cpl =0, cp=0;
	while (cx <= x2)
	{
		if (funcPts.size() < funcPts.max_size())
		{
			funcPts.push_back({ cx,func(a,b,c,cx) });
			cx += d;
			//std::cout << "cx = " << cx << "; d=" << d << "\n";
		}
		else
			break;
		i++;
		cp = (i*100 / n*100);
		if (cp != cpl) std::cout << (float)cp/(float)100 << ": ["<<i <<"/" << n <<"]"<< "%\n";
		cpl = cp;
	}

	//assign points to calculator
	iCalcRR.assignVector(funcPts);
	integNumeric = iCalcRR.getIntegral();
	printCalcCompar("Right Rectangles", integAnalyt, integNumeric);

	//end program
	system("pause");
}

