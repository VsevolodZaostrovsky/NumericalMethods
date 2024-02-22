#include "check.h"

double yk(int k, int n, int N)
{
    return sin(M_PI * (double)(n) * (double)(k) / (double)(N));
}

int main(void)
{
    double p = -10.;
    int N = 100;
    double h = 1 / (double)(N);
    double ans = 0;
    double lambdan = 0;

    for(int k = 1; k < N; k++)
    {
        for(int n = 1; n < N; n++)
        {
            ans = - yk(k + 1, n, N) + 2 * yk(k, n, N) - yk(k - 1, n, N) + p * h * h * yk(k, n, N);
            lambdan = p * h * h - 2 *(cos(M_PI * (double)(n) / (double)(N)) - 1.);
            if(ans - lambdan * yk(k, n, N) > 1e-4)
            {
                printf("for N = %d n = %d k = %d:\n %lf >> 0 --- test failed!!!\n\n", N, n, k, ans - lambdan * yk(k, n, N));
                return -1;
            }

        }
    }
    printf("for N = %d p = %lf all the tests passed \n ", N, p);
    return 0;
}