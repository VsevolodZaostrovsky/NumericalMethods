#include "PDE2dSolver.h"


void NextLayerFourierCoefs(double * LastLayer,  double (*f)(double, double, double), double h, double tau, int G,
                           double *Umatrix, double *Dmatrix, double *Cmatrix,
                           double *fmemory, double *netmemory, double *umemory, double *phimemory){
    

    
    int N = (int)(1. / (h));

    // GenerateNet(net, N - 1);

    for (int i = 1; i < N + 1; ++i)
    {
        for (int j = 1; j < N + 1; ++j)
        {
            if (i == 1 || i == N || j == 1 || j == N)
                Umatrix[e(i, j, N)] = 0;
            else
                Umatrix[e(i, j, N)] = LastLayer[e(i, j, N)] / tau + f(tau * (double)(G), h * (double)i , h * (double)j);
        }
    }

    FullDMatrix(Dmatrix, Umatrix, N, umemory, phimemory);
    FullCMatrix(Dmatrix, Cmatrix, N, fmemory, umemory, phimemory);
}

void CFromD(double * C, double * D, double h, double tau) 
{
    int N = (int)(1. / (h));
    double sinPih_n = 0;
    double sinPih_m = 0;

    for (int n = 1; n < N + 1; ++n)
    {
        for (int m = 1; m < N + 1; ++m)
        {
            if (n == 1 || n == N || m == 1 || m == N)
                C[e(n, m, N)] = 0;
            else {
                sinPih_n = sin(M_PI * (double)n * h / 2);
                sinPih_m = sin(M_PI * (double)m * h / 2);
                C[e(n, m, N)] = D[e(n, m, N)] / (4 / (h * h) * (sinPih_n * sinPih_n + sinPih_m * sinPih_m) + 1 / tau);
            }
        }
    }
}

double f(double x, double y, double t)
{
    return x * (1 - x) * y * (1 - y) * t;
}

int main(void){
    int N = 10;
    double h = 1./(double)N;
    double tau = 0.1;
    int G = 1;

    double *Umatrix;
    double *Dmatrix;
    double *Cmatrix;
    double *LastLayer;

    double *netmemory;
    double *fmemory;
    double *net;
    double *umemory;
    double *phimemory;


    Umatrix = (double *)malloc((N) * (N) * sizeof(double));
    Dmatrix = (double *)malloc((N) * (N) * sizeof(double));
    Cmatrix = (double *)malloc((N) * (N) * sizeof(double));
    LastLayer = (double *)malloc((N) * (N) * sizeof(double));
    for(int i = 0; i < N * N; i++){
        Umatrix[i] = 0; Dmatrix[i] = 0; Cmatrix[i] = 0; LastLayer[i] = 0;
    }

    netmemory = (double *)malloc((N + 5) * sizeof(double));
    fmemory = (double *)malloc((N + 5) * sizeof(double));
    net = (double *)malloc((N + 5) * sizeof(double));
    umemory = (double *)malloc((N + 5) * sizeof(double));
    phimemory = (double *)malloc((N + 5) * sizeof(double));


    NextLayerFourierCoefs(LastLayer,  f, h, tau, G, Umatrix, Dmatrix, Cmatrix, fmemory, net, netmemory, umemory, phimemory);

    free(Umatrix);
    free(Dmatrix);
    free(Cmatrix);
    free(LastLayer);

    free(netmemory);
    free(fmemory);
    free(net);
    free(umemory);
    free(phimemory);

    return 0;
}
