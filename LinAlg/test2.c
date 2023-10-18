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
    
    double * A;
    double * b;
    double * x;
    double * mem;

    A = (double *)malloc(N * N * sizeof(double));
    b = (double *)malloc(N * sizeof(double));
    x = (double *)malloc(N * sizeof(double));
    mem = (double *)malloc(N * sizeof(double));

    inp = fopen("inp.txt", "r");

    read_matrix(inp, A, N);

    FormBFromA(A, N, b);

    for (int k = 0; k < N; k++) 
    {
        printf("b[%d] = %20.15lf ", k, b[k]);
    }
    printf("\n");

    tau = FindTau(A, N);

    printf("tau = %20.15lf \n", tau);
    // Richardson(x, A, b, tau, N, eps, 3, mem);

    for(int m = 0; m < 50; m+=10) 
    {
        Richardson(x, A, b, tau, N, m, mem);
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
    free(b);
    free(x);
    free(mem);

    fclose(inp);

    return 0;
}
