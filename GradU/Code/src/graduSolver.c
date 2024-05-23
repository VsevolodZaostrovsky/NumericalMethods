#include "graduSolver.h"
#include <stdio.h>


void CFromD(double * C, double * D, double h, double tau) 
{
    int N_x = (int)(1. / (h)) + 1;
    double sinPih_n = 0;
    double sinPih_m = 0;

    for (int n = 1; n < N_x + 1; ++n)
    {
        for (int m = 1; m < N_x + 1; ++m)
        {
            if (n == 1 || n == N_x || m == 1 || m == N_x)
                C[e(n, m, N_x)] = 0;
            else {
                sinPih_n = sin(M_PI * (double)(n-1) * h * 0.5);
                sinPih_m = sin(M_PI * (double)(m-1) * h * 0.5);
                // C[e(n, m, N)] = D[e(n, m, N)] / (4 * (sinPih_n * sinPih_n + sinPih_m * sinPih_m) / (h * h) + 1. / tau);
                C[e(n, m, N_x)] = (D[e(n, m, N_x)]) / (4 / (h * h) * (sinPih_n * sinPih_n + sinPih_m * sinPih_m) + 1. / tau );
            }
        }
    }
}



void solveByR(double k, double h, double tau, // параметры, определяющие систему, которую нужно решить
              double * u,                     // сюда будет записан ответ
              double *RightPart,              // массив, содержащий правую часть уравнения
              double *Dmatrix, double *Cmatrix, double *fmemory, double *umemory, double *phimemory) 
{
    int N_x = (int)(1. / (h)) + 1;

    for (int i = 1; i < N_x + 1; ++i)
    {
        for (int j = 1; j < N_x + 1; ++j)
        {
            RightPart[e(i, j, N_x)] = RightPart[e(i, j, N_x)] / k;
        }
    }

    FullDMatrix(Dmatrix, RightPart, N_x, umemory, phimemory);

    FullCMatrix(Dmatrix, Cmatrix, N_x, fmemory, umemory, phimemory);


    CFromD(Dmatrix, Cmatrix, h, k * tau);

    CalcFourierMatrix(u, Dmatrix, N_x);
}

void multAb_kfunc(double tau, double h, double (*k)(double, double), double * b, double * ans)
{
    int N_x = (int)(1. / (h)) + 1;
    double h2rev  = 1. / (h * h);
    double taurev = 1. / tau;

    for(int i = 1; i < N_x + 1; i++) {
        for(int j = 1; j < N_x + 1; j++){
            if (i == 1 || i == N_x || j == 1 || j == N_x) ans[e(i, j, N_x)] = 0;
            else ans[e(i, j, N_x)] = b[e(i, j, N_x)] * (
                    taurev + (
                        k((i-1) * h + h * 0.5, (j-1) * h) 
                      + k((i-1) * h - h * 0.5, (j-1) * h)
                      + k((i-1) * h          , (j-1) * h + h * 0.5)
                      + k((i-1) * h          , (j-1) * h - h * 0.5)
                        ) * h2rev
                    ) 
                    -(
                        b[e(i + 1, j    , N_x)] * k((i-1) * h + h * 0.5, (j-1) * h) 
                      + b[e(i - 1, j    , N_x)] * k((i-1) * h - h * 0.5, (j-1) * h)
                      + b[e(i    , j + 1, N_x)] * k((i-1) * h          , (j-1) * h + h * 0.5)
                      + b[e(i    , j - 1, N_x)] * k((i-1) * h          , (j-1) * h - h * 0.5)
                    ) * h2rev;
        }
    }
}

void UnextFromU(double * Unext, double * U, double tau, double h, double (*k)(double, double), double * bmemory, double * LastMemory,
    double *Dmatrix, double *Cmatrix, double *fmemory, double *umemory, double *phimemory)
{
    int N_x = (int)(1. / (h)) + 1;
    double k_const = (k(0.05,0.05) + k(0.5, 0.5) + k(0.95, 0.95)) / 3.;
    double theta = 1.;
    double errorNorm = 100;
    int iteration = 0;
    // printf("k: %lf\n", k_const);

    for(int i = 0; i < N_x * N_x; i++)
            Unext[i] = U[i];

    while(errorNorm > 0.000001)
    {
        errorNorm = 0;

        multAb_kfunc(tau, h, k, Unext, bmemory);
        for(int i = 0; i < N_x * N_x; i++)
        {
            // printf("i%d b%lf \n", i, bmemory[i]);
            LastMemory[i] = Unext[i];
            bmemory[i] = U[i] - bmemory[i];
            errorNorm += bmemory[i] * bmemory[i];
        }
        errorNorm /= N_x * N_x;


        solveByR(k_const, h, tau, // параметры, определяющие систему, которую нужно решить
                  Unext,                     // сюда будет записан ответ
                  bmemory,              // массив, содержащий правую часть уравнения
                  Dmatrix, Cmatrix, fmemory, umemory, phimemory);

        
        for(int i = 0; i < N_x * N_x; i++)
            Unext[i] = theta * Unext[i] + LastMemory[i];
        
        iteration ++;
        printf("iteration %d error %lf\n", iteration, errorNorm);
        if(iteration > 10000) {
            printf("max iter reached \n\n\n\n");
            break;
        }
    }
    
}

void solvePDEgradu(double * uijn, int N, int N_x, double (*k)(double, double), double (*u0)(double, double), double * bmemory, double * LastMemory,
    double *Dmatrix, double *Cmatrix, double *fmemory, double *umemory, double *phimemory)
    {
    double h = 1./(double)(N_x-1);
    double tau = 1./(double)N;
    // printf("\ntotal %d\n", N);
    
    for(int i = 1; i < N_x + 1; i++){
        for(int j = 1; j < N_x + 1; j++){
            uijn[e(i, j, N_x)] = u0((i - 1) * h, (j - 1) * h);
        }
    }

    for (int G = 1; G < N; G++)
    {
        // printf("ok iter %d\n", G);
        UnextFromU(uijn + G * N_x * N_x, uijn + (G - 1) * N_x * N_x, tau, h, k, bmemory, LastMemory, Dmatrix, Cmatrix, fmemory, umemory, phimemory);
    }
    }
