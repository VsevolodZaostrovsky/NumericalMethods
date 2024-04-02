#include "SweepMethod.h"

int sweep_method(double * a, double * b, double * c, double * f, double * y, double * alpha, double * beta, int N) 
{
    alpha[0] = 0;
    beta[0] = 0;
    a[0] = 0;
    for(int i = 0; i < N - 1; i++)
    {
        alpha[i + 1] = b[i]                   / (c[i] - a[i] * alpha[i]);
        beta[i + 1] = (f[i] + a[i] * beta[i]) / (c[i] - a[i] * alpha[i]);
    }

    y[N] = (f[N] + a[N] * beta[N]) / (c[N] - a[N] * alpha[N]);
    for(int i = N - 1; i > -1; i--)
    {
        y[i] = alpha[i + 1] * y[i + 1] + beta[i + 1]; 
    }
    return 1;
}

// int main(void)
// {
//     double * a;
//     double * b;
//     double * c;
//     double * f;
//     double * y;
//     double * alpha;
//     double * beta;
//     int N = 2;
//     double am = 25.;

//     a     = (double *)malloc((N + 1) * sizeof(double));
//     b     = (double *)malloc((N + 1) * sizeof(double));
//     c     = (double *)malloc((N + 1) * sizeof(double));
//     f     = (double *)malloc((N + 1) * sizeof(double));
//     y     = (double *)malloc((N + 1) * sizeof(double));
//     alpha = (double *)malloc((N + 1) * sizeof(double));
//     beta  = (double *)malloc((N + 1) * sizeof(double));

//     a[0] = 100; a[1] = am; a[2] = am; a[3] = am; a[4] = am;
//     b[0] = am;  b[1] = am; b[2] = am; b[3] = am; b[4] = am;
//     c[0] = -2*am;  b[1] = -2*am; c[2] = -2*am; c[3] = -2*am; c[4] = -2*am;
//     f[0] =1; f[1] = 1; f[2] =1;

//     sweep_method(a, b, c, f, y, alpha, beta, N);

//     for(int k = 0; k < N+1; k ++){
//         printf("%10.15lf ", y[k]);
//     }
// }
