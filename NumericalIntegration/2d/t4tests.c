#include "Solution.h"

double f(double x, double y) {
    return x * x * x * x + y * y * x * x + y * y * y * y;
}


int main(int argc, char *argv[])
{
    int N = 100;
    double Lx = 1, Ly = 1;
    FILE *fp;
    FILE *sk;

    if (argc < 2)
    {
        printf("Wrong number of parameters, must be 1 in format:\n");
        printf("N \n");
        return -1;
    }

    N = atoi(argv[1]);

    printf("Ans: %20.15lf\n", Integrate(N, f));
    return 0;
}