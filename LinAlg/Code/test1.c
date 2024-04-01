#include "solution.h"

int main(int argc, char *argv[])
{
    int N = 6;
    double p = 0.;

    double *A;
    double *b;
    double *x;
    double *mem;

    if (argc < 3)
    {
        printf("Wrong number of parameters, must be 2 in format:\n");
        printf("N p \n");
        return -1;
    }

    N = atoi(argv[1]);
    p = atof(argv[2]); 

    A = (double *)malloc((N + 1) * (N + 1) * sizeof(double));
    b = (double *)malloc((N + 1) * sizeof(double));
    x = (double *)malloc((N + 1) * sizeof(double));
    mem = (double *)malloc((N + 1) * sizeof(double));

    FourierMatrix(p, N, A);
    printf("Matrix: \n");
    print_matrix(A, N + 1);
    // print_matrix(A, N + 1);

    FormBFromA(A, N, b);
    b[0] = 0;
    b[N] = 0;

    // b[1] = 18;
    // b[2] = 9;
    // print_vector(b, N + 1);
    // print_matrix(A, N + 1);
    // print_vector(mem, N + 1);

    // multMatrixByVector(A, mem, x, N + 1);

    // print_vector(x, N + 1);

    // printf("\n%20.15lf = %20.15lf\n\n", Lambdan(1, N, p), x[1] / mem[1]);

    // for(int n = 0; n < N + 1; n++) {
    // printf("%20.15lf", Dn(n, b, p, N) * psi(1, n, N));
    // }
    // printf("\n");

    // for(int n = 0; n < N + N; n++) {
    // printf("%20.15lf", Lambdan(n, N, p));
    // }
    // printf("\n");

    FourierMethod(x, N, p, b);

    // print_matrix(A, N + 1);
    
    printf("b: ");
    print_vector(b, N + 1);
    printf("ans: ");
    print_vector(x, N + 1);

    printf("norm = %20.15lf\n", ErNorm(A, b, x, N + 1, mem));

    // Richardson(x, A, b, tau, N, eps, 3, mem);

    free(A);
    free(b);
    free(x);
    free(mem);

    return 0;
}
