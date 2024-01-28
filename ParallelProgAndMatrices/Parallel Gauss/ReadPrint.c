#include <sys/resource.h>
#include <sys/time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "ReadPrint.h"

int max(int i, int j) {
	if(i > j) return i;
	return j;
}

double f(int i, int j, int s, int n)
{
	switch (s)
	{
	case 1:
		return (n - max(i, j) + 1);
		break;

	case 2:
		return max(i, j);
		break;

	case 3:
		return abs(i - j);
		break;

	case 4:
		return 1.0 / (1.0 + i + j);
		break;
        
    case 5:
        if(i == n) return 0;
        return abs(i - j);
		break;

	default:
        return 1;
		break;
	}
	return 0;
}

int ReadMatrix(int n, double *M, double *b, int s, char* filename)
{
	if (s == 0)
	{
		FILE *file;
		file = fopen(filename, "r");
		for (int i = 1; i < n + 1; i++)
		{
			for (int j = 1; j < n + 1; j++)
				if (!fscanf(file, "%lf", &M[e(i, j, n)]))
					return -1;
			if (!fscanf(file, "%lf", &b[i]))
				return -2;
		}
		fclose(file);
	}
	if (s == 1 || s == 2 || s == 3 || s == 4 || s == 5)
	{
		for (int i = 1; i < n + 1; i++)
		{
			for (int j = 1; j < n + 1; j++)
				M[e(i, j, n)] = f(i, j, s, n);

		}
		return 1;
	}
	else {
        for (int i = 1; i < n + 1; i++)
		{
			for (int j = 1; j < n + 1; j++)
				M[e(i, j, n)] = 0;

		}
		return -1;
    }
	return -3;
}

void PrintMatrix(int n, double *M, double *b, int r)
{
	if(r > n) {r = n;}
	for (int i = 1; i < r + 1; i++)
	{
		for (int j = 1; j < r + 1; j++)
			printf("%10.3e ", M[e(i, j, n)]);
		printf(" |   %10.3e\n", b[i - 1]);
	}
}

void PrintVector(int n, double *x, int r)
{
    int rr = r;
	printf("(");
    if(n < r) { rr = n; }
	for (int i = 0; i < rr; i++) {
		printf("%10.3e ", x[i]);
	}
	
	printf(")");
}

double TestSolution(int n, double *M, double *b, double *x)
{
	double result = 0.0;
    double tmp;
    
	for (int i = 1; i < n + 1; i++)
	{
		tmp = 0.0;
		for (int j = 1; j < n + 1; j++) tmp += M[e(i, j, n)] * x[j - 1];
		tmp -= b[i - 1];
		result += tmp * tmp;
	}
	return result;
}

double Accuracy(int n, double *x)
{
	double tmp;
	double result;

	result = 0.0;
	for (int i = 0; i < n; i++)
	{
		tmp = x[i];
		if (!(i%2)) tmp -= 1.0;
		result += tmp * tmp;
	}
	return result;
}

void FullVector(double* v, double* m, int n) {
    for (int i = 1; i < n + 1; i++)
    {
        double sum = 0;
        for (int j = 1; j < n + 1; j += 2)
        {
            if(m[e(i, j, n)] > 1e-100 || m[e(i, j, n)] < -1e-100) sum += m[e(i, j, n)];
        }
        v[i - 1] = sum;
    }
}
