#include "2dFourierApprox.h"
#include "PDE2dSolver.h"
#include <math.h>


void CFromD(double * C, double * D, double h, double tau) ;



void solveByR(double k, double h, double tau, // параметры, определяющие систему, которую нужно решить
              double * u,                     // сюда будет записан ответ
              double *RightPart,              // массив, содержащий правую часть уравнения
              double *Dmatrix, double *Cmatrix, double *fmemory, double *umemory, double *phimemory) ;


void solvePDEgradu(double * uijn, int N, int N_x, double (*k)(double, double), double (*u0)(double, double), double * bmemory, double * LastMemory,
    double *Dmatrix, double *Cmatrix, double *fmemory, double *umemory, double *phimemory);