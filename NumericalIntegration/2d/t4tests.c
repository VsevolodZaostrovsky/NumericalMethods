#include "Solution.h"
#include <math.h>

double f(double x, double y);

double f(double x, double y) {
    return x * x * x * x  + y * x * y * x + y * y * y * y;
}


int main(int argc, char *argv[])
{
    int N;
    int ON;
    double ca = 23. / 45.;
    FILE *fp;

    if (argc < 3)
    {
        printf("Wrong number of parameters, must be 2 in format:\n");
        printf("N filename\n");
        return -1;
    }

    if ((fp = fopen(argv[2], "w")) == NULL) // имя файла, в который нужно записать ответ
    {
        printf("Не удалось открыть файл\n");
        return 0;
    }

    N = atoi(argv[1]);

    printf("Ans: %20.15lf\n Ca: %20.15lf\n", Integrate(N, f), ca);
    printf("p =  %20.15lf\n", (Integrate(N, f) - Integrate(N + 20, f) / (log(N) - log(N + 20))));

    ON = N;
    for (int k = 1; k < 50; ++k)
    {
        N = ON + k;
        fprintf(fp, "%20.15lf %20.15lf\n", log(N), log(fabs(Integrate(N, f) - ca)));
    }
    fclose(fp);
    return 0;
}
