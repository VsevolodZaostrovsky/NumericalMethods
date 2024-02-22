#include "Useful.h"
#include "Scheme.h"

int main(void)
{
    double * x;
    double * y;
    double * ans;
    double * realans;
    double * mem;
    double * mem1;
    double * mem2;
    double * mem3;
    FILE *file;

    double h = 0.01;

    int N = 2;

    x        = (double*) malloc(N * sizeof(double));
    y        = (double*) malloc(N * sizeof(double));
    ans      = (double*) malloc(N * sizeof(double));
    realans  = (double*) malloc(N * sizeof(double));
    mem      = (double*) malloc(N * sizeof(double));
    mem1     = (double*) malloc(N * sizeof(double));
    mem2     = (double*) malloc(N * sizeof(double));
    mem3     = (double*) malloc(N * sizeof(double));

    x[0] = 0;
    y[0] = 1;

    x[1] = 0;
    y[1] = -1;

    file = fopen("out4.txt", "w");


    for(int j = 1; j < (int)(1. / h); j++)
    {

        sol4(x, y, realans, N);
        E(x, y, ans, N, h, f4, mem, mem1, mem2, mem3);

        fprintf(file, "%e %e %e %e %e %e %e\n", x[0], realans[0], realans[1], y[0], y[1], L0norm(realans, y, N), L0normOne(ans, N));

        yNext(x, y, ans, N, h, f4, mem, mem1, mem2, mem3);
        y[0] = ans[0];
        x[0] += h;
        y[1] = ans[1];
        x[1] += h;
        printf("%lf, ", y[0]);
        printf("%lf, ", y[1]);

    }
    printf("\n");
    

    free(x);
    free(y);
    free(ans);
    free(mem);
    free(mem1);
    free(mem2);
    free(mem3);
    free(realans);
    
    fclose(file);
}