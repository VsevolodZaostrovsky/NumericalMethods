#pragma once
#include <iostream>
#include <math.h>
#include <cstring>

#include "vector.hpp"
#include "Matrix.hpp"

void ToAlmostDiagRefl(double* matrix, double* X,  int n, double eps);

void QRdecomposition(double *matrix, double *X, 
    double *U1, double *U2, int n, int subn, double eps);

void RQ(double *matrix, double *U1, double *U2, int n, int subn); 

void QRshift(double *matrix, double *X, double *U1, 
    double *U2, double* ans, int n, int subn, double eps, double MatrNormEps);

int Eignvalues(double* matrix, double* X, double* U1, 
    double* U2, double* ans, int n, double epsans);