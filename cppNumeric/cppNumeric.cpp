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

//derivative of our function; c is deprecated in the case of parabola
double funcDDeriv(double a, double b, double c, double x)
{
	return 2 * a*x + b;
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
	ncTrapezoid iCalcTr;
	ncSimpson iCalcSm;
	ncDerivative iCalcDr;
	ncBasicMin iCalcMinSrc;
	ncGoldenDiv iCalcMinGD;
	std::cout << "Input a,b,c,x1,x2,d,derSP\n";
	double a, b, c, x1, x2, d, dsp;
	std::cin >> a >> b >> c >> x1 >> x2 >> d >> dsp;

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
		if (cp != cpl) std::cout << (float)cp/(float)100 << "%: ["<<i <<"/" << n <<"]"<< "\n";
		cpl = cp;
	}

	// ++ find defined integral ++
	//Right Rectangles
	//assign points to calculator
	iCalcRR.assignVector(funcPts);
	integNumeric = iCalcRR.getNumericValue();
	printCalcCompar("Right Rectangles", integAnalyt, integNumeric);

	//Trapezoid
	//assign points to calculator
	iCalcTr.assignVector(funcPts);
	integNumeric = iCalcTr.getNumericValue();
	printCalcCompar("Trapezoid", integAnalyt, integNumeric);

	//Simpson
	//assign points to calculator
	iCalcSm.assignVector(funcPts);
	integNumeric = iCalcSm.getNumericValue();
	printCalcCompar("Simpson", integAnalyt, integNumeric);

	//++ find derivative at a point ++

	integAnalyt = funcDDeriv(a, b, c, dsp);

	//by discrete values
	//assign points to calculator
	iCalcDr.assignVector(funcPts);
	iCalcDr.setDerivativeSearchPoint(dsp);
	integNumeric = iCalcDr.getNumericValue();
	printCalcCompar("Discrete derivative", integAnalyt, integNumeric);

	//by analytical function expression
	iCalcDr.setBaseFunc(func);
	iCalcDr.setDerivPrecision(d/10000);
	integNumeric = iCalcDr.getDerivativeByFunction(a, b, c);
	printCalcCompar("Semianalytical derivative", integAnalyt, integNumeric);

	//++find function minimum++
	//hard search
	iCalcMinSrc.assignVector(funcPts);
	integAnalyt = iCalcMinSrc.getNumericValue();

	//golden section
	iCalcMinGD.setBaseFunc(func);
	iCalcMinGD.setFuncCoeffs(a, b, c);
	iCalcMinGD.setPrecision(d);
	iCalcMinGD.setDiapason(x1, x2);
	integNumeric = iCalcMinGD.getNumericValue();
	printCalcCompar("Golden Section Search min:", integAnalyt, integNumeric);

	//end program
	system("pause");
}

