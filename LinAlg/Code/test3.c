#include "solution.h"


int main(int argc, char *argv[])
{
    int N = 3;
    double p = 0;
    double eps = 0;
    double tau = 0.1;
    double q = 0;
    double dq = 1;
    double fnorm = 0;
    double evm = 0;
    double evM = 0;
    int mIter = 1000;
    double temp = 0;

    FILE *out;

    double *A;
    double *B;
    double *b;
    double *x;
    double *mem;
    double *mem1;

    if (argc < 5)
    {
        printf("Wrong number of parameters, must be 4 in format:\n");
        printf("N m p filename \n where N - matrix dim, m - num of iterations, p - parametr of Gauss matrix, filename - the name of the file with computation info \n");
        return -1;
    }

    N = atoi(argv[1]);
    mIter = atoi(argv[2]);
    p = atof(argv[3]);

    out = fopen(argv[4], "w");

    A = (double *)malloc(N * N * sizeof(double));
    B = (double *)malloc(N * N * sizeof(double));
    b = (double *)malloc((N + 1) * sizeof(double));
    x = (double *)malloc((N + 1) * sizeof(double));
    mem = (double *)malloc((N + 1) * sizeof(double));
    mem1 = (double *)malloc((N + 1) * sizeof(double));

    A[0]  = 4; A[1]  = 0; A[2]  = 1;  A[3] = 0;   b[0] = 19;
    A[4]  = 0; A[5]  = 3; A[6]  = 0;  A[7] = 0;   b[1] = 9;
    A[8]  = 1; A[9]  = 0; A[10] = 9;  A[11] = 0;  b[2] = 101;
    A[12] = 0; A[13] = 0; A[14] = 0;  A[15] = 5;  b[3] = 10;

    B[0] = 0.25; B[1] = 0; B[2] = 0; B[3] = 0;
    B[4] = 0; B[5] = 0.3333333333; B[6] = 0; B[7] = 0;
    B[8] = 0; B[9] = 0; B[10] = 0.111111111111; B[11] = 0;
    B[12] = 0; B[13] = 0; B[14] = 0; B[15] = 0.2; 

    eps = BSolver(x, A, B, b, tau, 4, mIter, mem, mem1);

    printf("ans: "); print_vector(x, 4);

    printf("eps = %20.15lf\n", eps);

    Task3Matrix(A, N - 1);

    // print_matrix(A, N - 1);

    for(int k = 0; k < (N - 1) * (N - 1); k++) 
    {
        if(k % (N - 1) == k / (N - 1)) B[k] = 1./ A[k];
        else B[k] = 0;
    }

    FormBFromA1(A, N - 1, b);

    // ReverseFourierMatrixWithoutZeros(p, B, N, mem, mem1);

    eps = BSolver(x, A, B, b, tau, N - 1, mIter, mem, mem1);

    printf("ans: "); print_vector(x, N - 1);

    printf("eps = %20.15lf\n", eps);

//    print_matrix(A, N - 1);

    q = Findq(A, N - 1);
    fnorm = BSolver(x, A, B, b, tau, N - 1, 0, mem, mem1);

    for (int n = 1; n < mIter; n += 1)
    {
        eps = BSolver(x, A, B, b, tau, N - 1, n, mem, mem1);
        fprintf(out, "%d %20.15lf %20.15lf \n", n, eps, dq * fnorm);
        dq *= q;
    }

    // printf("Norm: %20.15lf\n", ErNormInf(A, b, x, N - 1, mem));

    // print_matrix(A, N - 1);
    // print_matrix(B, N - 1);




    free(A);
    free(B);
    free(b);
    free(x);
    free(mem);
    free(mem1);

    fclose(out);


    return 0;
}