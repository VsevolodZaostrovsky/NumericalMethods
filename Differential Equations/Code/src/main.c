#include <stdlib.h>
#include <math.h>
#include <stdio.h>


double solution1(double y0, double A, double h, double* y) { 
    int N = (int)(1 / h);
    y[0] = y0;
    for(int k = 1; k < N; k++){
        y[k] = y[k - 1] * (1 - A * h);
    }
    return 1; 
    }

double solution2(double y0, double A, double h, double* y) { 
    int N = (int)(1 / h);
    y[0] = y0;
    for(int k = 1; k < N; k++){
        y[k] = y[k - 1] / (1 + A * h);
    }
    return 1; 
    }

double solution3(double y0, double A, double h, double* y) { 
    int N = (int)(1 / h);
    y[0] = y0;
    for(int k = 1; k < N; k++){
        y[k] = y[k - 1] * (2 - A * h) / (2 + A * h);
    }
    return 1; 
    }

double solution4(double y0, double y1, double A, double h, double* y) { 
    int N = (int)(1 / h);
    y[0] = y0;
    for(int k = 1; k < N; k++){
        y[k] = y[k - 1] - 2 * A * h * y[k - 2];
    }
    return 1; 
    }

double solution5(double y0, double y1, double A, double h, double* y) { 
    int N = (int)(1 / h);
    y[0] = y0;
    for(int k = 1; k < N; k++){
        y[k] = (2 * y[k - 1] - 0.5 * y[k - 2]) / (1.5 + A * h);
    }
    return 1; 
    }

double solution6(double y0, double y1, double A, double h, double* y) { 
    int N = (int)(1 / h);
    y[0] = y0;
    for(int k = 1; k < N; k++){
        y[k] = 2 * ((A * h - 3) * y[k - 2] + 4 * y[k - 1]); 
    }
    return 1; 
    }

double ans(double h, double A, double* y) { 
    int N = (int)(1 / h);
    for(int k = 0; k < N; k++){
        y[k] = exp(- A * k * h);
    }
    return 1; 
    }

double L0norm(double *x, double *y, int len) {
    double max = fabs(x[0] - y[0]);
    for(int i = 1; i < len; i++) {
        if (fabs(x[i] - y[i]) > max) {
            max = fabs(x[i] - y[i]);
        }
    }
    return max;
}


int main(void) {
    int N = 1e6;
    double A = 1;
    double h = 1 / (double)(N);

    double *xans;
    double *x;

    xans = (double*) malloc(N * sizeof(double));
    x    = (double*) malloc(N * sizeof(double));

    ans(h, A, xans);
    // solution2(1., A, h, x);
    // solution3(1., A, h, x);
    // solution4(1., 1. - A * h, A, h, x);
    // solution5(1., 1. - A * h, A, h, x);
    // solution6(1., 1. - A * h, A, h, x);

    FILE *S1;
    S1 = fopen("out.txt", "w");
    fprintf(S1, " \\begin\{table\}[h!] \n\\begin\{center\} \n\\begin\{tabular\}\{|c|c|c|c|c|c|\} \n\\hline \nНомер  & $E_1 & $E_2$ & $E_3$ & $E_6$ & $m$ & $A$ \\\\ \\hline"); 
    fprintf(S1, "\n 1 & ");   
    for(int j = 0; j < 3; j++) {
        switch (j)
            {
            case 0: A = 1;   break;
            case 1: A = 10;  break;
            case 2: A = 1000; break;
            default: break;
            }
        for(int i = 0; i < 4; i++) {
            switch (i)
            {
            case 0: h = 0.1;   break;
            case 1: h = 0.01;  break;
            case 2: h = 0.001; break;
            case 3: h = 1e-6;  break;
            default: break;
            }

            solution1(1., A, h, x);
            fprintf(S1, " $%lf$ &", L0norm(xans, x, (int)(1 / h)));
        }
        fprintf(S1, " $m$ & %lf \\\\ \\hline \n", A);
    }

        fprintf(S1, "\n 2 & ");   
    for(int j = 0; j < 3; j++) {
        switch (j)
            {
            case 0: A = 1;   break;
            case 1: A = 10;  break;
            case 2: A = 1000; break;
            default: break;
            }
        for(int i = 0; i < 4; i++) {
            switch (i)
            {
            case 0: h = 0.1;   break;
            case 1: h = 0.01;  break;
            case 2: h = 0.001; break;
            case 3: h = 1e-6;  break;
            default: break;
            }

            solution2(1., A, h, x);
            fprintf(S1, " $%lf$ &", L0norm(xans, x, (int)(1 / h)));
        }
        fprintf(S1, " $m$ & %lf \\\\ \\hline \n", A);
    }

        fprintf(S1, "\n 3 & ");   
    for(int j = 0; j < 3; j++) {
        switch (j)
            {
            case 0: A = 1;   break;
            case 1: A = 10;  break;
            case 2: A = 1000; break;
            default: break;
            }
        for(int i = 0; i < 4; i++) {
            switch (i)
            {
            case 0: h = 0.1;   break;
            case 1: h = 0.01;  break;
            case 2: h = 0.001; break;
            case 3: h = 1e-6;  break;
            default: break;
            }

            solution3(1., A, h, x);
            fprintf(S1, " $%lf$ &", L0norm(xans, x, (int)(1 / h)));
        }
        fprintf(S1, " $m$ & %lf \\\\ \\hline \n", A);
    }

        fprintf(S1, "\n 4 & ");   
    for(int j = 0; j < 3; j++) {
        switch (j)
            {
            case 0: A = 1;   break;
            case 1: A = 10;  break;
            case 2: A = 1000; break;
            default: break;
            }
        for(int i = 0; i < 4; i++) {
            switch (i)
            {
            case 0: h = 0.1;   break;
            case 1: h = 0.01;  break;
            case 2: h = 0.001; break;
            case 3: h = 1e-6;  break;
            default: break;
            }

            solution4(1., 1. - A*h, A, h, x);
            fprintf(S1, " $%lf$ &", L0norm(xans, x, (int)(1 / h)));
        }
        fprintf(S1, " $m$ & %lf \\\\ \\hline \n", A);
    }

        fprintf(S1, "\n 5 & ");   
    for(int j = 0; j < 3; j++) {
        switch (j)
            {
            case 0: A = 1;   break;
            case 1: A = 10;  break;
            case 2: A = 1000; break;
            default: break;
            }
        for(int i = 0; i < 4; i++) {
            switch (i)
            {
            case 0: h = 0.1;   break;
            case 1: h = 0.01;  break;
            case 2: h = 0.001; break;
            case 3: h = 1e-6;  break;
            default: break;
            }

            solution5(1., 1. - A*h, A, h, x);
            fprintf(S1, " $%lf$ &", L0norm(xans, x, (int)(1 / h)));
        }
        fprintf(S1, " $m$ & %lf \\\\ \\hline \n", A);
    }

        fprintf(S1, "\n 6 & ");   
    for(int j = 0; j < 3; j++) {
        switch (j)
            {
            case 0: A = 1;   break;
            case 1: A = 10;  break;
            case 2: A = 1000; break;
            default: break;
            }
        for(int i = 0; i < 4; i++) {
            switch (i)
            {
            case 0: h = 0.1;   break;
            case 1: h = 0.01;  break;
            case 2: h = 0.001; break;
            case 3: h = 1e-6;  break;
            default: break;
            }

            solution6(1., 1. - A*h, A, h, x);
            fprintf(S1, " $%lf$ &", L0norm(xans, x, (int)(1 / h)));
        }
        fprintf(S1, " $m$ & %lf \\\\ \\hline \n", A);
    }

    fprintf(S1, "\end\{tabular\} \n\\end\{center\}\\caption\{Требуемая табличка\}.\} \n\\label\{Aggreg1CU\} \\end\{table\} \n "); 
    
    free(x);
    free(xans);
    fclose(S1);

}
    


