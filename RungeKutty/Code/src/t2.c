#include "Useful.h"
#include "Scheme.h"

int main(void)
{
    double * x;
    double * y;
    double * ans;
    double * mem;
    double * mem1;
    double * mem2;
    double * mem3;

    int N = 1;

    x    = (double*) malloc(N * sizeof(double));
    y    = (double*) malloc(N * sizeof(double));
    ans  = (double*) malloc(N * sizeof(double));
    mem  = (double*) malloc(N * sizeof(double));
    mem1 = (double*) malloc(N * sizeof(double));
    mem2 = (double*) malloc(N * sizeof(double));
    mem3 = (double*) malloc(N * sizeof(double));

    x[0] = 0;
    y[0] = 1;

    for(int j = 1; j < 101; j++)
    {
        yNext(x, y, ans, N, 0.01, f2, mem, mem1, mem2, mem3);
        y[0] = ans[0];
        x[0] += 0.01;
        printf("%lf, ", y[0]);

    }
    printf("\n");
    

    free(x);
    free(y);
    free(ans);
    free(mem);
    free(mem1);
    free(mem2);
    free(mem3);
}