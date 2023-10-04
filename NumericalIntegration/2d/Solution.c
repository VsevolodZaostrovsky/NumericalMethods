#include "Solution.h"

void WriteTriangulation(int N, double Lx, double Ly, FILE *out)
{
    int isedge = 1;
    double hx = Lx / N;
    double hy = Ly / N;
    int leftup = 0;
    int number = 1;
    fprintf(out, "%lf %lf\n", hx, hy);       
    fprintf(out, "%d\n", (N + 1) * (N + 1)); // num of nodes
    fprintf(out, "%d\n", N * N * 2);         // num of triangles
    fprintf(out, "%d\n", (3 * N + 2) * N);   // num of triangles
    fprintf(out, "%d\n", 4 * N);             // num of edge nodes

    for (int i = 0; i < (N + 1) * (N + 1); ++i)
    {
        fprintf(out, "%d: %20.15lf %20.15lf \n", i + 1, (i % (N + 1)) * hx, (i / (N + 1)) * hy);
    }

    for (int j = 1; j < N + 1; ++j)
    {
        for (int i = 1; i < N + 1; ++i)
        {
            leftup = i + (j - 1) * (N + 1);
            fprintf(out, "%d: %d %d %d \n", 2 * (i + (j - 1) * N) - 1, leftup, leftup + 1, leftup + N + 1);
            fprintf(out, "%d: %d %d %d \n", 2 * (i + (j - 1) * N), leftup + 1, leftup + N + 1, leftup + N + 2);
        }
    }

    for (int j = 1; j < N + 1; ++j)
    {
        for (int i = 1; i < N + 1; ++i) 
        {
            leftup = i + (j - 1) * (N + 1);
            if(i == 1 && j == 1) {
                fprintf(out, "%d: %d %d \n", number, 2, N + 2);
                number++;
            }
            else if(i == 1) {
                fprintf(out, "%d: %d %d\n", number, leftup, leftup + 1);
                number++;
                fprintf(out, "%d: %d %d\n", number, leftup + 1, leftup + N + 1);
                number++;
            }
            else if(j == 1) {
                fprintf(out, "%d: %d %d\n", number, leftup, leftup + N + 1);
                number++;
                fprintf(out, "%d: %d %d\n", number, leftup + 1, leftup + N + 1);
                number++;
            }
            else {
                fprintf(out, "%d: %d %d\n", number, leftup, leftup + 1);
                number++;
                fprintf(out, "%d: %d %d\n", number, leftup + 1, leftup + N + 1);
                number++;
                fprintf(out, "%d: %d %d\n", number, leftup + 1, leftup + N + 1);
                number++;
            }
        }
    }

    number = 1;
    for (int j = 1; j < N + 1; ++j)
    {
        fprintf(out, "%d: %d %d\n", number, j, j + 1);
        number++;
    }

    for (int j = 0; j < N; ++j)
    {
        fprintf(out, "%d: %d %d\n", number, j * (N + 1) + 1, j * (N + 1) + N + 2);
        number++;
        fprintf(out, "%d: %d %d\n", number, j * (N + 1) + 1 + N, j * (N + 1) + 1 + N + N + 1);
        number++;
    }

    for (int j = 1; j < N + 1; ++j)
    {
        fprintf(out, "%d: %d %d\n", number, (N + 1) * N + j, (N + 1) * N + 1 + j);
        number++;
    }
}

double Integrate(int N, double (*f)(double, double))
{
    double ans = 0;
    int leftup = 0;
    int an, cn, bn;
    double anx, any, bnx, bny, cnx, cny;
    double h = 1 / (double)(N);

    for (int j = 1; j < N + 1; ++j)
    {
        for (int i = 1; i < N + 1; ++i)
        {
            an = i + (j - 1) * (N + 1);
            bn = an + 1;
            cn = bn + N + 1;
            anx = (an % (N + 1)) * h;
            any = (an / (N + 1)) * h;
            bnx = (bn % (N + 1)) * h;
            bny = (bn / (N + 1)) * h;
            cnx = (cn % (N + 1)) * h;
            cny = (cn / (N + 1)) * h;

            ans += 0.5 * h * h* (f((anx + bnx)/2, (any + bny)/2) + f((anx + cnx)/2, (any + cny)/2) + f((cnx + bnx)/2, (cny + bny)/2)) / 3;

            an = i + (j - 1) * (N + 1) + 1;
            bn = an + N + 1;
            cn = bn + N + 2;
            anx = (an % (N + 1)) * h;
            any = (an / (N + 1)) * h;
            bnx = (bn % (N + 1)) * h;
            bny = (bn / (N + 1)) * h;
            cnx = (cn % (N + 1)) * h;
            cny = (cn / (N + 1)) * h;

            ans += 0.5 * h * h * (f((anx + bnx)/2, (any + bny)/2) + f((anx + cnx)/2, (any + cny)/2) + f((cnx + bnx)/2, (cny + bny)/2)) / 3;
        }
    }
    

    return ans;

}