#pragma once
#include <math.h>
#include <cmath>
#include <iostream>

double f(double x){
	return exp(-0.3 * x * x) - sqrt(x) + 1.0;  //оригинал
}
double f_(double x){
	return (f(x + 0.0000001) - f(x - 0.0000001)) / 0.0000002; //производная
}
double fx(double x){
	return exp(-0.6 * x * x) + 2 * sqrt(x) - 1.0;  //преобразованное ур-ние в вид x = f(x)
}													//надо постараться найти хорошее преобразование 



//оригиналы
double f1(double x1, double x2){
	return sin(x1 - 1) + x2 - 1.5;
}
double f2(double x1, double x2){
	return x1 - sin(x2 - 1) - 1;
}
//центральные разностные частные производные 
double f1_x1(double x1, double x2) {
	return (f1(x1 + 0.0000001, x2) - f1(x1 - 0.0000001, x2)) / 0.0000002;
}
double f1_x2(double x1, double x2) {
	return (f1(x1, x2 + 0.0000001) - f1(x1, x2 - 0.0000001)) / 0.0000002;
}
double f2_x1(double x1, double x2) {
	return (f2(x1 + 0.0000001, x2) - f2(x1 - 0.0000001, x2)) / 0.0000002;
}
double f2_x2(double x1, double x2) {
	return (f2(x1, x2 + 0.0000001) - f2(x1, x2 - 0.0000001)) / 0.0000002;
}


//НЕ НАДО ВОТ ТАК ДЕЛАТЬ!!!!!
/*
double f1_x1(double x1, double x2){
	return cos(x1 - 1);
}
double f1_x2(double x1, double x2){
	return 1;
}
double f2_x1(double x1, double x2){
	return 1;
}
double f2_x2(double x1, double x2){
	return -cos(x2 - 1);
}

//ТЕМ БОЛЕЕ ВОТ ТАК

double F(double x1, double x2) {
	return sin(x1-1)* sin(x1 - 1) + 2 * x2 * sin(x1 - 1) - 3 * sin(x1 - 1) + x2*x2 - 3*x2 + 2.25       + x1 * x1 + sin(x2 - 1) * sin(x2 - 1) + 1 - 2 * x1 * sin(x2 - 1) - 2 * x1 + 2 * sin(x2 - 1);	
}
double F_x1(double x1, double x2) {
	return 2 * sin(x1 - 1) * cos(x1 - 1) + 2 * x2 * cos(x1 - 1) - 3 * cos(x1 - 1) + 2 * x1 + - 2 * sin(x2 - 1) - 2;
}
double F_x2(double x1, double x2) {
	return 2 * sin(x1 - 1) + 2 * x2 - 3 + 2 * sin(x2 - 1) * cos(x2 - 1) - 2 * x1 * cos(x2 - 1) + 2 * cos(x2 - 1);
}
double F_x1x1(double x1, double x2) {
	return 2 * cos(x1 - 1) * cos(x1 - 1) - 2 * sin(x1 - 1) * sin(x1 - 1) - 2 * x2 * sin(x1 - 1) + 3 * sin(x1 - 1) + 2;
}
double F_x1x2(double x1, double x2) {
	return 2 * x2 * cos(x1 - 1) + 2 * sin(x1 - 1) - 2 * x1 * cos(x2 - 1) - 2 * sin(x2 - 1);
}
double F_x2x2(double x1, double x2) {
	return x2 + 2 * cos(x2 - 1) * cos(x2 - 1) - 2 * sin(x2 - 1) * sin(x2 - 1) + 2 * x1 * sin(x2 - 1) - 2 * sin(x2 - 1);
}
double F_x2x1(double x1, double x2) {
	return 2 * x2 * cos(x1 - 1) + 2 * sin(x1 - 1) - 2 * x1 * cos(x2 - 1) - 2 * sin(x2 - 1);
}
*/

//оригинал
double F(double x1, double x2) {
	return pow(f1(x1, x2), 2) + pow(f2(x1, x2), 2);
}
//центральные разностные первые и вторые частные производные 
double F_x1(double x1, double x2) {
	return (F(x1 + 0.0000001, x2) - F(x1 - 0.0000001, x2)) / 0.0000002; 
}
double F_x2(double x1, double x2) {
	return (F(x1 , x2 + 0.0000001) - F(x1, x2 - 0.0000001)) / 0.0000002; 
}
double F_x1x1(double x1, double x2) {
	return (F_x1(x1 + 0.0000001, x2) - F_x1(x1 - 0.0000001, x2)) / 0.0000002;
}
double F_x1x2(double x1, double x2) {
	return (F_x1(x1, x2 + 0.0000001) - F_x1(x1, x2 - 0.0000001)) / 0.0000002;
}
double F_x2x2(double x1, double x2) {
	return (F_x2(x1 , x2 + 0.0000001) - F_x2(x1 , x2 - 0.0000001)) / 0.0000002;
}
double F_x2x1(double x1, double x2) {
	return (F_x2(x1 + 0.0000001, x2) - F_x2(x1 - 0.0000001, x2)) / 0.0000002;
}




void Gaussian(double **A, double* B, double* x) 
{
	double Anew[2][2];

	Anew[0][0] = A[0][0];
	Anew[0][1] = A[0][1];
	Anew[1][0] = A[1][0];
	Anew[1][1] = A[1][1];

	double K = Anew[1][0] / Anew[0][0];
		Anew[1][0] -= Anew[0][0] * K;
		Anew[1][1] -= Anew[0][1] * K;
		B[1] -= B[0] * K;

	x[1] = B[1] / Anew[1][1];
	x[0] = (B[0] - Anew[0][1] * x[1]) / Anew[0][0];
}

double max(double a, double b)
{
	if (abs(a) >= abs(b))
		return a;
	if (abs(a) < abs(b))
		return b;
}