#include "SweepMethod.h"

double func(double t, double x){ return 0; }

double p(double x){ return 0; }

double u0(double x){ return sin(M_PI * x); }


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


    h   = 1. / (double)(N);
    tau = 1. / (double)(M);

    a     = (double *)malloc((M + N + 1) * sizeof(double));
    b     = (double *)malloc((M + N + 1) * sizeof(double));
    c     = (double *)malloc((M + N + 1) * sizeof(double));
    f     = (double *)malloc((M + N + 1) * sizeof(double));
    y     = (double *)malloc((M + N + 1) * sizeof(double));
    alpha = (double *)malloc((M + N + 1) * sizeof(double));
    beta  = (double *)malloc((M + N + 1) * sizeof(double));
    differentialNet = (double *)malloc(N * M * sizeof(double));
    for(int k = 0; k < M; k++){ differentialNet[k] = u0(k * h); }

    for(int i = 0; i < N - 2; i++)
    {
        for(int k = 0; k < M - 2; k++)
        {
            a[k] = 1 / (h * h);
            b[k] = 1 / (h * h);
            c[k] = 1 / tau + 2 / (h * h) + p((i + 1) * h);
        }


        for(int k = 0; k < M - 2; k++)
        {
            f[k] = func((k+2) * tau, i * h) + differentialNet[M * i + k + 1] / tau;
            //  printf("%lf \n", f[k]);
        }

        for(int k = 0; k < M - 2; k++)
        {
            // printf("%lf %lf %lf %lf\n", a[k], b[k], c[k], f[k]);
        }


        sweep_method(a, b, c, f, y, alpha, beta, M - 3);
        for(int k = 0; k < M - 2; k++)
        {
            // printf("%lf \n", y[k]);
        }
        for(int k = 0; k < M - 2; k++){ 
            differentialNet[M * (i + 1) + k + 1] = y[k]; 
        // printf("%lf ", y[k]);
        }
        differentialNet[M * (i + 1) + 0] = 0;
        differentialNet[M * (i + 1) + N - 1] = 0;
    }
    

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
            printf("%10.5lf ", differentialNet[i * N + j]);
        printf("\n");
    }
    printf("\n");
    // for(int i = 0; i < N; i++)
    // {
    //     for(int j = 0; j < M; j++)
    //         printf("%10.5lf ", sin(M_PI * j * h) * exp(-M_PI * M_PI * i * tau));
    //     printf("\n");
    // }
    // printf("\n");


    free(a);
    free(b);
    free(c);
    free(f);
    free(y);
    free(alpha);
    free(beta);

    return 0;
}
