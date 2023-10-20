#include "solution.h"

int main(int argc, char *argv[])
{
    int N = 3;
    int m = 10;
    double p = 0;
    double eps = 1e-10;
    double tau = 0.1;
    double q = 0;
    double dq = 0;
    double fnorm = 0;
    double evm = 0;
    double evM = 0;


    double *A;
    double *b;
    double *x;
    double *mem;

    FILE *out;

    if (argc < 5)
    {
        printf("Wrong number of parameters, must be 4 in format:\n");
        printf("N m p filename \n where N - matrix dim, m - num of iterations, p - parametr of Gauss matrix, filename - the name of the file with computation info \n");
        return -1;
    }

    N = atoi(argv[1]);
    m = atoi(argv[2]);
    p = atof(argv[3]);

    A = (double *)malloc(N * N * sizeof(double));
    b = (double *)malloc(N * sizeof(double));
    x = (double *)malloc(N * sizeof(double));
    mem = (double *)malloc(N * sizeof(double));

    out = fopen(argv[4], "w");

    FourierMatrixWithoutZeros(p, N, A); 
    FormBFromA(A, N, b);

    evm = Lambdan(1, N + 1, p);
    evM = Lambdan(N, N + 1, p);

    tau = 2. / (evm + evM);

    // printf("tau = %20.15lf \n", tau);
    // Richardson(x, A, b, tau, N, eps, 3, mem);

    q = (evM - evm) / (evM + evm);
    dq = 1;
    printf("q = %20.15lf \n", q);
    fnorm = Richardson(x, A, b, tau, N, 0, mem);

    for (int n = 0; n < m; n += 1)
    {
        eps = Richardson(x, A, b, tau, N, n, mem);
        fprintf(out, "%d %20.15lf %20.15lf \n", n, eps, dq * fnorm);
        dq *= q;
    }

    // // print_matrix(A, N);

    // for(int i = 0; i < N * N; i++) {
    //     printf("%20.15lf ", A[i]);
    // }
    // printf("\n");

    printf("Norm: %20.15lf \n", ErNorm(A, b, x, N, mem));
    // printf("q: %20.15lf \n", q);
    // print_matrix(A, N);

    fclose(out);

    free(A);
    free(b);
    free(x);
    free(mem);

    return 0;
}
