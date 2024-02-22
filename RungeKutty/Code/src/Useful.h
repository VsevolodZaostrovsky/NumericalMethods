#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void f1(double   x, double * y, double * ans, int n);
void f2(double   x, double * y, double * ans, int n);
void f3(double   x, double * y, double * ans, int n);
void sol3(double x, double * y, double * ans, int n);
void f4(double   x, double * y, double * ans, int n);
void sol4(double x, double * y, double * ans, int n);
void f5(double   x, double * y, double * ans, int n);
void sol5(double x, double * y, double * ans, int n);


void printArr(double * x, int n);

double L0norm(double *x, double *y, int len);

double L0normOne(double *x, int len);