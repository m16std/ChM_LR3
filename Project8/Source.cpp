#include "Header.h"

double Dihtomia(double left, double right, double point)
{
	if ((f(left) > point && f(right) > point) || (f(left) < point && f(right) < point))
	{
		std::cout << "ERROR";
		return 0;
	}

	double x;

	if (f(left) > point && f(right) < point)
	{
		x = left;
		left = right;
		right = x;
	}

	while (abs(left - right) > 0.000001)
	{
		std::cout << "\n\t" << left << "\t" << right;

		x = (left + right) / 2.0;

		if (f(x) > point)
			right = x;
		else
			left = x;
	}

	return (left + right) / 2.0;
}

double Newton(double xn)
{
	double xnplus1 = xn + 0.1;

	while (abs(xn - xnplus1) > 0.000001)
	{
		std::cout << "\n\t" << xn;
		xn = xnplus1;
		xnplus1 = xn - f(xn) / f_(xn);
	}

	return xnplus1;
}

double Simple_iteration(double xn)
{
	double xnplus1 = xn + 0.1;
	double count = 0;
	while (abs(xn - xnplus1) > 0.000001 && count < 100)
	{
		std::cout << "\n\t" << xn;
		xn = xnplus1;
		xnplus1 = fx(xn);
		count++;
	}

	return xnplus1;
}

double Sekuschie(double xn)
{
	double xnplus1 = xn + 0.1;
	double xnminus1 = xn - 0.1;

	while (abs(xn - xnplus1) > 0.000001)
	{
		std::cout << "\n\t" << xn;
		xnminus1 = xn;
		xn = xnplus1;
		xnplus1 = xn - (xn - xnminus1) * f(xn) / ( f(xn) - f(xnminus1));
	}

	return xnplus1;
}

void Newton_system(double x1n, double x2n)
{
	double delta = 0.1;
	double **M, F[2], x[2];

	M = new double* [2];
	for (int i = 0; i < 2; i++)
		M[i] = new double[2];

	while (abs(delta) > 0.00000001)
	{
		M[0][0] = f1_x1(x1n, x2n);
		M[0][1] = f1_x2(x1n, x2n);
		M[1][0] = f2_x1(x1n, x2n);
		M[1][1] = f2_x2(x1n, x2n);

		F[0] = -f1(x1n, x2n);
		F[1] = -f2(x1n, x2n);

		/*
		for (int i = 0; i < 2; i++)
		{
			std::cout << "\n";
			for (int j = 0; j < 2; j++)
				std::cout << "\t" << M[i][j];
			std::cout << "\t" << F[i];
		}
		std::cout << "\n";
		*/

		Gaussian(M, F, x);

		delta = max(x[0], x[1]);

		std::cout << "\n\t" << x1n << "\t" << x2n;

		x1n += x[0];
		x2n += x[1];
	}

	std::cout << "\nAnswer: " << x1n << "\t" << x2n << "\n";
}

void Newton_mod(double x1n, double x2n)
{
	double delta = 0.1, count = 0;
	double** M, F[2], x[2];

	M = new double* [2];
	for (int i = 0; i < 2; i++)
		M[i] = new double[2];

	M[0][0] = f1_x1(x1n, x2n);
	M[0][1] = f1_x2(x1n, x2n);
	M[1][0] = f2_x1(x1n, x2n);
	M[1][1] = f2_x2(x1n, x2n);

	while (abs(delta) > 0.00000001 && count < 200)
	{
		F[0] = -f1(x1n, x2n);
		F[1] = -f2(x1n, x2n);

		Gaussian(M, F, x);

		/*
		std::cout << "\n";
		for (int i = 0; i < 2; i++)
		{
			std::cout << "\n";
			for (int j = 0; j < 2; j++)
				std::cout << "\t" << M[i][j];
			std::cout << "\t" << F[i];
		}
		std::cout << "\n";
		*/

		delta = max(x[0], x[1]);

		std::cout << "\n\t" << x1n << "\t" << x2n;

		x1n += x[0];
		x2n += x[1];
		count++;
	}

	std::cout << "\nAnswer: " << x1n << "\t" << x2n << "\n";
}

void Newton_two_stage(double x1n, double x2n)
{
	double delta = 0.1;
	double** M, F[2], x[2];

	M = new double* [2];
	for (int i = 0; i < 2; i++)
		M[i] = new double[2];

	while (abs(delta) > 0.00000001)
	{
		M[0][0] = f1_x1(x1n, x2n);
		M[0][1] = f1_x2(x1n, x2n);
		M[1][0] = f2_x1(x1n, x2n);
		M[1][1] = f2_x2(x1n, x2n);

		F[0] = -f1(x1n, x2n);
		F[1] = -f2(x1n, x2n);

		/*
		for (int i = 0; i < 2; i++)
		{
			std::cout << "\n";
			for (int j = 0; j < 2; j++)
				std::cout << "\t" << M[i][j];
			std::cout << "\t" << F[i];
		}
		std::cout << "\n";
		*/

		Gaussian(M, F, x);

		std::cout << "\n\t" << x1n << "\t\t" << x2n;

		x1n += x[0];
		x2n += x[1];

		F[0] = -f1(x1n, x2n);
		F[1] = -f2(x1n, x2n);

		Gaussian(M, F, x);
		
		delta = max(x[0], x[1]);

		std::cout << "\n\t" << x1n << "\t" << x2n << "\t";

		x1n += x[0];
		x2n += x[1];
	}

	std::cout << "\nAnswer: " << x1n << "\t" << x2n << "\n";
}

void Newton_min(double x1n, double x2n)
{
	double count = 0, delta = 1;
	double** M, F[2], x[2];

	M = new double* [2];
	for (int i = 0; i < 2; i++)
		M[i] = new double[2];

	while (abs(delta) > 0.00000001 && count < 200)
	{

		M[0][0] = F_x1x1(x1n, x2n);
		M[0][1] = F_x1x2(x1n, x2n);
		M[1][0] = F_x2x1(x1n, x2n);
		M[1][1] = F_x2x2(x1n, x2n);

		F[0] = -F_x1(x1n, x2n);
		F[1] = -F_x2(x1n, x2n);

		Gaussian(M, F, x);

		/*
		std::cout << "\n";
		for (int i = 0; i < 2; i++)
		{
			std::cout << "\n";
			for (int j = 0; j < 2; j++)
				std::cout << "\t" << M[i][j];
			std::cout << "\t" << F[i];
		}
		std::cout << "\n";
		*/

		delta = max(x[0], x[1]);

		std::cout << "\n\t" << x1n << "\t" << x2n;

		x1n += x[0];
		x2n += x[1];

		count++;
	}

	std::cout << "\nAnswer: " << x1n << "\t" << x2n << "\n";
}

int main()
{
	std::cout.precision(7);
	std::cout << "\n\n~~~~~~~~Equation solution~~~~~~~~\n\n";
	std::cout << "\n\t~~~Dihtomia method~~~";
	std::cout << "\nAnswer: " << Dihtomia(0.1, 5, 0) << "\n";
	std::cout << "\n\t~~~Newton method~~~";
	std::cout << "\nAnswer: " << Newton(0.1) << "\n";
	std::cout << "\n\t~~~Simple iteration method~~~";
	std::cout << "\nAnswer: " << Simple_iteration(0.1) << "\n";
	std::cout << "\n\t~~~Method sekuschih~~~";
	std::cout << "\nAnswer: " << Sekuschie(0.1) << "\n";
	std::cout << "\n\n~~~~~~~~System solutions~~~~~~~~\n\n";
	std::cout << "\n\t~~~Newton method~~~";
	Newton_system(3, 3);
	std::cout << "\n\t~~~Modified Newton method~~~";
	Newton_mod(1.5, 1.5); //начальные значения должны быть близки к искомым, а то не сработает магия
	std::cout << "\n\t~~~Newton two-stage method~~~";
	Newton_two_stage(3, 3);
	std::cout << "\n\n~~~~~~~~Equation solution~~~~~~~~\n\n";
	std::cout << "\n\t~~~Newton method for minimum~~~";
	Newton_min(3, 3);
	std::cout << "\n\nWORK DONE :3\n\n";
}