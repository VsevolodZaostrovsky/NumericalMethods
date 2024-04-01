#include "FourierMethod.h"

double f(x, y){ return 0; }

double full_b_f(double * b, double (*f)(double), int start, int end, double h){
    double delta = 0;
    for(int j = start; j < end; j++) {
        b[j] = f(delta);
        delta += h;
    }
}

int main(int argc, char *argv[])
{
    int N = 6;
    double p = 0.;
    double *b;
    double *x;
    double *mem;

    if (argc < 3)
    {
        printf("Wrong number of parameters, must be 2 in format:\n");
        printf("N p \n");
        return -1;
    }

    N = atoi(argv[1]);
    p = atof(argv[2]); 

    b = (double *)malloc((N + 1) * sizeof(double));
    x = (double *)malloc((N + 1) * sizeof(double));
    mem = (double *)malloc((N + 1) * sizeof(double));

    FourierMethod(x, N, p, b);
    
    printf("b: ");
    print_vector(b, N + 1);
    printf("ans: ");
    print_vector(x, N + 1);


    free(b);
    free(x);
    free(mem);

    return 0;
}
