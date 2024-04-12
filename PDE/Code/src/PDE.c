#include "SweepMethod.h"

double func(double t, double x){ return 0; }

double p(double x){ return 0; }

double u0(double x){ return 0; }

double u1(double x){ return 0; }


int main(int argc, char *argv[])
{
    double * a;
    double * b;
    double * c;
    double * f;
    double * y;
    double * differentialNet;
    double * alpha;
    double * beta;
    double delta = 0;
    int N = 0;
    int M = 0;
    double h = 0;
    double tau = 0;

    if (argc < 3)
    {
        printf("Wrong number of parameters, must be 1 in format:\n");
        printf("N M\n");
        return -1;
    }

    N = atoi(argv[1]);
    M = atoi(argv[2]);


    h = (double)(1 / N);
    tau = (double)(1 / M);

    a     = (double *)malloc((N + 1) * sizeof(double));
    b     = (double *)malloc((N + 1) * sizeof(double));
    c     = (double *)malloc((N + 1) * sizeof(double));
    f     = (double *)malloc((N + 1) * sizeof(double));
    y     = (double *)malloc((N + 1) * sizeof(double));
    alpha = (double *)malloc((N + 1) * sizeof(double));
    beta  = (double *)malloc((N + 1) * sizeof(double));
    differentialNet = (double *)malloc((N + 1) * (M + 1) * sizeof(double));
    for(int k = 0; k < M + 1; k++){ differentialNet[k] = 0; }

    for(int i = 0; i < N - 1; i++)
    {
        for(int k = 0; k < M - 1; k++)
        {
            a[k] = 1 / (h * h);
            b[k] = 1 / (h * h);
            c[k] = 1 / tau + 2 / (h * h) + p(i * h);
        }


        for(int k = 0; k < M - 1; k++)
        {
            f[k] = func((k+1) * tau, i * h) + differentialNet[(M - 1) * i + k + 1];

        }

        sweep_method(a, b, c, f, y, alpha, beta, N - 2);
        for(int k = 0; k < M - 1; k++){ differentialNet[(M - 1) * (i + 1) + k + 1] = y[k]; }
        differentialNet[(M - 1) * (i + 1) + 0] = u0(i * h);
        differentialNet[(M - 1) * (i + 1) + N] = u1(i * h);
    }
    

    for(int i = 0; i < N + 1; i++)
        for(int j = 0; j < M + 1; j++)
            printf("%10.15lf ", differentialNet[j]);
        print("\n");
    printf("\n");

    free(a);
    free(b);
    free(c);
    free(f);
    free(y);
    free(alpha);
    free(beta);

    return 0;
}
