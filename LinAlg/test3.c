#include "solution.h"


int main(void)
{
    int N = 5;
    int m = 10;
    double eps = 1e-10;
    double tau = 0.1;
    double p = 5.;

    FILE *inp;
    FILE *inp1;

    double *A;
    double *B;
    double *b;
    double *x;
    double *mem;
    double *mem1;

    A = (double *)malloc(N * N * sizeof(double));
    B = (double *)malloc(N * N * sizeof(double));
    b = (double *)malloc((N + 1) * sizeof(double));
    x = (double *)malloc((N + 1) * sizeof(double));
    mem = (double *)malloc((N + 1) * sizeof(double));
    mem1 = (double *)malloc((N + 1) * sizeof(double));

    FourierMatrixWithoutZeros(p, N - 1, A);

    ReverseFourierMatrixWithoutZeros(p, B, N, mem1, mem);

    // print_matrix(A, N - 1);
    // print_matrix(B, N - 1);




    free(A);
    free(B);
    free(b);
    free(x);
    free(mem);
    free(mem1);


    return 0;
}