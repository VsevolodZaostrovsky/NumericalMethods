#include "SweepMethod.h"
#include "FourierMethod.h"

double func(double x){ return 1; }

double p(int k){ return 1; }

double full_b_f(double * b, double (*f)(double), int N){
    double h = (double)(1 / (N + 1));
    double delta = h;
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
    double * alpha;
    double * beta;
    int N = 0;

    if (argc < 2)
    {
        printf("Wrong number of parameters, must be 1 in format:\n");
        printf("N number of points - 1\n");
        return -1;
    }

    N = atoi(argv[1]);

    a     = (double *)malloc((N + 1) * sizeof(double));
    b     = (double *)malloc((N + 1) * sizeof(double));
    c     = (double *)malloc((N + 1) * sizeof(double));
    f     = (double *)malloc((N + 1) * sizeof(double));
    y     = (double *)malloc((N + 1) * sizeof(double));
    alpha = (double *)malloc((N + 1) * sizeof(double));
    beta  = (double *)malloc((N + 1) * sizeof(double));

    for(int k = 0; k < N+1; k++)
    {
        a[k] = (double)((N) * (N));
        b[k] = (double)((N) * (N));
        c[k] = 2*(double)((N) * (N)) + p(k);
    }

    full_b_f(f, func, N);
    sweep_method(a, b, c, f, y, alpha, beta, N);


    printf("%10.15lf ", 0.);
    for(int k = 0; k < N; k ++)
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
