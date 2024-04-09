#include "SweepMethod.h"

double f(double x, double t){ return 0; }

double p(double x){ return 0; }

double full_b_f(double * b, double (*f)(double), int N){
    double delta = 0;
    double h = (double)(1 / N);
    for(int j = 0; j < N; j++) {
        b[j] = f(delta);
        delta += h;
    }
}

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

    if (argc < 3)
    {
        printf("Wrong number of parameters, must be 1 in format:\n");
        printf("N M\n");
        return -1;
    }

    N = atoi(argv[1]);
    M = atoi(argv[2]);


    delta = (double)(1/N);

    a     = (double *)malloc((N + 10000) * sizeof(double));
    b     = (double *)malloc((N + 10000) * sizeof(double));
    c     = (double *)malloc((N + 10000) * sizeof(double));
    f     = (double *)malloc((N + 10000) * sizeof(double));
    y     = (double *)malloc((N + 10000) * sizeof(double));
    alpha = (double *)malloc((N + 10000) * sizeof(double));
    beta  = (double *)malloc((N + 10000) * sizeof(double));
    differentialNet = (double *)malloc((N + 1) * (M + 1) * sizeof(double));
    
    for(int k = 0; k < N - 1; k++)
    {
        a[k] = (double)((N) * (N));
        b[k] = (double)((N) * (N));
        c[k] = 2*(double)((N) * (N)) + p((double)(k) / (double)((N) * (N)));
        // c[k] = 2*(double)((N) * (N)) + 1;
    }
    // a[N - 2] = b[0];
    // c[N - 2] = c[0];
    // b[0] = (double)((N) * (N));

    delta += (double)(1/N); 
    for(int k = 0; k < N; k++)
    {
        f[k] = func(delta);
        // f[k] = 1;
        delta += (double)(1/N);
    }

    sweep_method(a, b, c, f, y, alpha, beta, N - 2);

    for(int k = 0; k < N - 1; k ++)
        printf("%10.15lf ", y[k]);
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
