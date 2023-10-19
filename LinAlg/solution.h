#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double psi(int k, int n, int N);

double Lambdan(int n, int N, double p);

double Dn(int n, double * f, double p, int N);

void multMatrixByVector(const double *A, double *x, double *ans, int N);

double Richardson(double *x, const double *A, const double *b, double tau, int n, int mIter, double *mem);

double FindTau(const double *A, int n);

double FourierMethod(double * x, int N, double p, double * f);

void FormBFromA(double *A, int N, double * b);

double BSolver(double *x, const double *A, const double *B, const double *b, double tau, int n, int mIter, double *mem, double *mem1);

double ErNorm(const double * A, const double * b, double * x, int N, double * mem);

void FourierMatrix(double p, int N, double * M);

int read_matrix(FILE *inp, double *matrix, int dim);

void print_matrix(double * A, int N);

void print_vector(double * A, int N);

void FourierMatrixWithoutZeros(double p, int N, double *M);

double Findq(const double *A, int n);

void ReverseFourierMatrixWithoutZeros(double p, double * B, int N, double * mem1, double * mem2);