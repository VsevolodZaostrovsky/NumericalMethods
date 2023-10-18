#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void multMatrixByVector(const double *A, double *x, double *ans, int N);

double Richardson(double *x, const double *A, const double *b, double tau, int n, int mIter, double *mem);

double FindTau(const double *A, int n);

double FourierMethod(double * x, int N, double p, double * f);

void FormBFromA(double *A, int N, double * b);

double BSolver(double *x, const double *A, const double *B, const double *b, double tau, int n, int mIter, double *mem, double *mem1);