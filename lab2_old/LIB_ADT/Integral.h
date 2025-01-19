#ifndef INTEGRATION_API_H
#define INTEGRATION_API_H

typedef double (*FuncPointer)(double x);

double simpsonRule(FuncPointer f, double a, double b, int n);
double func(double x);


#endif