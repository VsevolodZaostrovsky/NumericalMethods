#include "solution.h"

int read_matrix(FILE *inp, double *matrix, int dim) {
    for (int i = 0; i < dim * dim; ++i) 
    {
        fscanf(inp, "%lf", &matrix[i]);
    }
	return 1;
}



int main(void) 
{
    int N = 3;
    int m = 10;
    double eps = 1e-10;
    double tau = 0.1;

    FILE *inp;
    FILE *inp1;
    
    double * A;
    double * B;
    double * b;
    double * x;
    double * mem;
    double * mem1;

    A = (double *)malloc(N * N * sizeof(double));
    B = (double *)malloc(N * N * sizeof(double));
    b = (double *)malloc(N * sizeof(double));
    x = (double *)malloc(N * sizeof(double));
    mem = (double *)malloc(N * sizeof(double));
    mem1 = (double *)malloc(N * sizeof(double));

    inp = fopen("inp.txt", "r");
    inp1 = fopen("inp1.txt", "r");

    read_matrix(inp, A, N);
    read_matrix(inp1, B, N);

    FormBFromA(A, N, b);

    for (int k = 0; k < N; k++) 
    {
        printf("b[%d] = %20.15lf ", k, b[k]);
    }
    printf("\n");

    tau = FindTau(A, N);

    printf("tau = %20.15lf \n", tau);
    // Richardson(x, A, b, tau, N, eps, 3, mem);

    for(int m = 0; m < 500; m+=100) 
    {
        BSolver(x, A, B, b, tau, N, m, mem, mem1);
        for(int k = 0; k < N; k++) 
        {
            printf("%20.15lf ", m, x[k]);
        }
        printf("\n");
    }

    // for(int i = 0; i < N * N; i++) {
    //     printf("%20.15lf ", A[i]);
    // }
    // printf("\n");

    free(A);
    free(B);
    free(b);
    free(x);
    free(mem);
    free(mem1);

    fclose(inp);
    fclose(inp1);

    return 0;
}