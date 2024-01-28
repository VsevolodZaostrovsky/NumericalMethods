#pragma once

#define e(i, j, n) ((i-1)*(n) + (j-1))

int max(int i, int j);

double f(int i, int j, int s, int n);

int ReadMatrix(int n, double *M, double *b, int s, char* filename);

void PrintMatrix(int n, double *M, double *b, int r);

void PrintVector(int n, double *x, int r);

double TestSolution(int n, double *M, double *b, double *x);

double Accuracy(int n, double *x);

void FullVector(double* v, double* m, int n);


