#include "Useful.h"
#include "Scheme.h"

int main(void)
{
    double x;
    double * y;
    double * ans;
    double * mem;
    double * mem1;
    double * mem2;
    double * mem3;

    int N = 2;

    y    = (double*) malloc(N * sizeof(double));
    ans  = (double*) malloc(N * sizeof(double));
    mem  = (double*) malloc(N * sizeof(double));
    mem1 = (double*) malloc(N * sizeof(double));
    mem2 = (double*) malloc(N * sizeof(double));
    mem3 = (double*) malloc(N * sizeof(double));

    x = 0;
    y[0] = 1;
    y[1] = -1;

    for(int j = 1; j < 101; j++)
    {
        // k1(x, y, mem3, N, 0.01, f2);
        // printf("\nk1 %lf, ", mem3[0]);
        // k4(x, y, mem3, N, 0.01, f2, mem, mem1, mem2);
        // printf("k4 %lf, ", mem3[0]);
        // k5(x, y, mem3, N, 0.01, f2, mem, mem1, mem2);
        // printf("k5 %lf \n", mem3[0]);

        yNext(x, y, ans, N, 0.01, f3, mem, mem1, mem2, mem3);
        y[0] = ans[0];
        y[1] = ans[1];
        x += 0.01;

        printf("%lf, ", y[0]);
        printf("%lf, ", y[1]);

    }
    printf("\n");
    

    free(y);
    free(ans);
    free(mem);
    free(mem1);
    free(mem2);
    free(mem3);
}