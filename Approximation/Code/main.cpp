#include "Pn.hpp"
#include "Ln.hpp"

#include "knots.cpp"

double module(double x)
{
    return -x * (x < 0) + x * (x > 0);
}

double f(double x)
{
    return 1 / (1 + 25 * x * x);
}

void PrintTable(double *knots, int N, Pn *P, Ln *L, double (*f)(double))
{
    printf("   Knotes               Pn                   Ln                   f\n");
    for (int i = 0; i < N - 1; ++i)
    {
        double xi = knots[i];
        printf("%20.15lf %20.15lf %20.15lf %20.15lf \n", xi, P->calculate(xi), L->calculate(xi), f(xi));
        double xi1 = 2 * xi / 3 + knots[i + 1] / 3;
        printf("%20.15lf %20.15lf %20.15lf %20.15lf \n", xi1, P->calculate(xi1), L->calculate(xi1), f(xi1));
        double xi2 = xi / 3 + 2 * knots[i + 1] / 3;
        printf("%20.15lf %20.15lf %20.15lf %20.15lf \n", xi2, P->calculate(xi2), L->calculate(xi2), f(xi2));
    }
    double xi = knots[N - 1];
    printf("%20.15lf %20.15lf %20.15lf %20.15lf \n", xi, P->calculate(xi), L->calculate(xi), f(xi));
}

void WriteResult(double *knots, int N, Pn *P, Ln *L, double (*f)(double), FILE *out)
{
    for (int i = 0; i < N - 1; ++i)
    {
        double xi = knots[i];
        fprintf(out, "%20.15lf %20.15lf %20.15lf %20.15lf \n", xi, P->calculate(xi), L->calculate(xi), f(xi));
        double xi1 = 2 * xi / 3 + knots[i + 1] / 3;
        fprintf(out, "%20.15lf %20.15lf %20.15lf %20.15lf \n", xi1, P->calculate(xi1), L->calculate(xi1), f(xi1));
        double xi2 = xi / 3 + 2 * knots[i + 1] / 3;
        fprintf(out, "%20.15lf %20.15lf %20.15lf %20.15lf \n", xi2, P->calculate(xi2), L->calculate(xi2), f(xi2));
    }
    double xi = knots[N - 1];
    fprintf(out, "%20.15lf %20.15lf %20.15lf %20.15lf \n", xi, P->calculate(xi), L->calculate(xi), f(xi));
}

void WriteSkrypt(int N, int k, double a, double b, char *testfilename, FILE *out)
{
    std::string kn;

    if (k)
        kn = "Chebyshev";
    else
        kn = "Equidistant";

    fprintf(out, "#! /usr/bin/gnuplot -persist\n");
    fprintf(out, "set terminal png size 1000,1000 enhanced font \"Helvetica Bold, 20\"\n");
    fprintf(out, "set output \"%s.png\"\n\n", testfilename);

    fprintf(out, "set style line 1 lt 1 linecolor rgb \"red\" lw 1 pt 1\n");
    fprintf(out, "set style line 2 lt 1 linecolor rgb \"blue\" lw 1 pt 1\n");
    fprintf(out, "set style line 3 lt 1 linecolor rgb \"green\" lw 1 pt 1\n\n");

    //    fprintf(out, "set yrange [0:5]");
    fprintf(out, "set xrange [%lf:%lf]\n", a, b);

    fprintf(out, "set title \"%s - %d %s knots \"\n", testfilename, N, kn.c_str());

    fprintf(out, "set grid\n\n");

    fprintf(out, "plot  \"%s\" using 1:2 ls 1 title \"Interpolation Gauss Polynom\" with lines, ", testfilename);
    fprintf(out, "\"%s\" using 1:4 ls 2 title \"Original function\", ", testfilename);
    fprintf(out, "\"%s\" using 1:3 ls 3 title \"Lagrange function\" with lines", testfilename);
}

int main(int argc, char *argv[])
{
    if (argc < 6)
    {
        std::cout << "Wrong number of parameters, must be 5 in format:\n"
                  << "N k a b name \n"
                  << "where: \n N - number of knots \n k - type of knots (0 - Equidistant or 1 - Chebyshev) \n [a, b] - interval of approx \n name - name of the file with answer \n";
        return -1;
    }

    int N = atoi(argv[1]);    // число узлов
    int k = atoi(argv[2]);    // тип узлов
    double a = atof(argv[3]); // левая
    double b = atof(argv[4]); // и правая границы отрезка
    FILE *fp;
    FILE *sk;
    int flag = 0;

    if (N <= 1)
    {
        std::cout << "Wrong N: it must be 1\n";
        return -1;
    }
    if (a >= b)
    {
        std::cout << "Wrong k: it must be 0 or 1\n";
        return -1;
    }
    if (k != 1 && k != 0)
    {
        std::cout << "Wrong k (=" << k << "): it must be 0 or 1\n";
        return -1;
    }
    double *knots1 = new double[N];
    double *knots2 = new double[N];
    double *mean1 = new double[N];
    double *mean2 = new double[N];

    try
    {
        if (k)
        {
            std::cout << "Chebyshev Grid generated\n";
            GenerateChebyshevGrid(a, b, N, f, knots1, mean1);
            GenerateChebyshevGrid(a, b, N, f, knots2, mean2);
        }
        else
        {
            std::cout << "Equidistant Grid generated\n";
            GenerateEquidistantGrid(a, b, N, f, knots1, mean1);
            GenerateEquidistantGrid(a, b, N, f, knots2, mean2);
        }

        Ln L(N, knots2, mean2);
        std::cout << "Lagr Polynom built\n";

        Pn P(N, knots1, mean1);
        std::cout << "Polynom built: \n";
        P.print();

        if (argv[5][0] == 'n' && argv[5][1] == 'o' && argv[5][2] == 't')
        {
            flag = 1;
            std::cout << "not in file\n";
        }

        if (flag == 0 && (fp = fopen(argv[5], "w+")) == NULL) // имя файла, в который нужно записать ответ
        {
            printf("Не удалось открыть файл");
            return 0;
        }

        if (flag)
            PrintTable(knots1, N, &P, &L, f);
        else
        {
            WriteResult(knots1, N, &P, &L, f, fp);
            if ((sk = fopen("printAll.gpi", "w+")) == NULL) 
            {
                printf("Не удалось открыть файл");
                fclose(fp);
                return 0;
            }
            WriteSkrypt(N, k, a, b, argv[5], sk);
            fclose(fp);
            fclose(sk);
        }
    }
    catch (const char *error_message)
    {
        std::cout << error_message << std::endl;
    }

    delete[] knots2;
    delete[] knots1;
    delete[] mean2;
    delete[] mean1;

    return 0;
}