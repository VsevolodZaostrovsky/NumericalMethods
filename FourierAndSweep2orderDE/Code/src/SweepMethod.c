#include "SweepMethod.h"

int sweep_method(double * a, double * b, double * c, double * f, double * y, double * alpha, double * beta, int N) 
{
    /* На самом деле, система должна иметь размер N+1, здесь я следую обозначеням Чижонкова Бахвалова и Корнева*/
    alpha[0] = 0;
    beta[0] = 0;
    a[0] = 0;

    alpha[1] = b[0] / c[0];
    beta[1] = f[0] / c[0];
    for(int i = 1; i < N; i++)
    {
        alpha[i + 1] = b[i]                   / (c[i] - a[i] * alpha[i]);
        beta[i + 1] = (f[i] + a[i] * beta[i]) / (c[i] - a[i] * alpha[i]);
    }

    y[N] = (f[N] + a[N] * beta[N]) / (c[N] - a[N] * alpha[N]);

    for(int i = N - 1; i > -1; i--)
    {
        y[i] = alpha[i + 1] * y[i + 1] + beta[i + 1]; 
        // printf("y%d %lf  \n\n", i, y[i]);
    }
    return 1;
}

// int main(int argc, char *argv[])
// {
//    double * a;
//     double * b;
//     double * c;
//     double * f;
//     double * y;
//     double * alpha;
//     double * beta;
//     double delta = 0;
//     int N = 0;

//     if (argc < 2)
//     {
//         printf("Wrong number of parameters, must be 1 in format:\n");
//         printf("N number of points - 1\n");
//         return -1;
//     }

//     N = atoi(argv[1]);


//     delta = (double)(1/N);

//     a     = (double *)malloc((N + 10000) * sizeof(double));
//     b     = (double *)malloc((N + 10000) * sizeof(double));
//     c     = (double *)malloc((N + 10000) * sizeof(double));
//     f     = (double *)malloc((N + 10000) * sizeof(double));
//     y     = (double *)malloc((N + 10000) * sizeof(double));
//     alpha = (double *)malloc((N + 10000) * sizeof(double));
//     beta  = (double *)malloc((N + 10000) * sizeof(double));


//     // c[0] = 2*(double)((N) * (N)) + p(1);
    
//     for(int k = 0; k < N - 1; k++)
//     {
//         a[k] = (double)((N) * (N));
//         b[k] = (double)((N) * (N));
//         // c[k] = 2*(double)((N) * (N)) + p(k);
//         c[k] = 2*(double)((N) * (N)) + 1;
//     }
//     a[N - 2] = b[0];
//     c[N - 2] = c[0];
//     c[0] = 2*(double)((N) * (N)) + 1;
//     b[0] = (double)((N) * (N));

//     delta += (double)(1/N); 
//     for(int k = 0; k < N; k++)
//     {
//         // f[k] = func(delta);
//         f[k] = 1;
//         delta += (double)(1/N);
//     }

//     sweep_method(a, b, c, f, y, alpha, beta, N - 2);

//     for(int k = 0; k < N - 1; k ++)
//         printf("%10.15lf ", y[k]);
//     printf("\n");

//     free(a);
//     free(b);
//     free(c);
//     free(f);
//     free(y);
//     free(alpha);
//     free(beta);

//     return 0;
// }


