#include "QRRefl.hpp"

double norm(double* _value, int _N) {
    double sum = 0;
	double summax = 0;

	for (int i = 1; i <= _N; i++)
	{
		for (int j = 1; j <= _N; j++)
		{
			sum += abs(_value[e(i, j, _N)]);
		}
		if (sum > summax)
		{
			summax = sum;
		}
	}
	return summax;
}

void ToAlmostDiagRefl(double *matrix, double *X, int n, double eps)
{
    int k, j, i;
    for(k = 1; k < n - 1; k++)
    {
        //вычислили необходимые константы
        double Sk = 0;
        for(i = k + 2; i < n + 1; i++)
            Sk += matrix[e(i, k, n)] * matrix[e(i, k, n)];

        double norm_a1 = sqrt(Sk + matrix[e(k + 1, k, n)] * matrix[e(k + 1, k, n)]);

        X[k] = matrix[e(k + 1, k, n)] - norm_a1;
        for(i = k + 1; i < n; i++)
            X[i] = matrix[e(i + 1, k, n)];

        double norm_x = sqrt(Sk + X[k] * X[k]);

        if(norm_x > eps)
        {
            //вычислили искомый вектор х
            double B = 1 / norm_x;
            for(i = k; i < n; i++)
                X[i] *= B;

            //умножаем исходную матрицу на матрицу отражения слева
            double scalar_prodact = 0;
            for(j = k; j < n + 1; j++)
            {
                scalar_prodact = 0;
                for(i = k + 1; i < n + 1; i++)
                    scalar_prodact += X[i - 1] * matrix[e(i, j, n)];
                scalar_prodact = -scalar_prodact;
                for(i = k + 1; i < n + 1; i++)
                    matrix[e(i, j, n)] += 2 * X[i - 1] * scalar_prodact;
            }

            //умножаем матрицу на матрицу отражения справа
            for(i = 1; i < n + 1; i++)
            {
                scalar_prodact = 0;
                for(j = k + 1; j < n + 1; j++)
                    scalar_prodact += X[j - 1] * matrix[e(i, j, n)];
                scalar_prodact = -scalar_prodact;
                for(j = k + 1; j < n + 1; j++)
                    matrix[e(i, j, n)] += 2 * X[j - 1] * scalar_prodact;
            }
        }
    }
}

void QRdecomposition(double *matrix, double *X, double *U1, double *U2, int n, int subn, double eps)
{
    int k, j, i;
    for(k = 1; k < subn; k++)
    {
        //вычислили необходимые константы
        double Sk = matrix[e(k + 1, k, n)] * matrix[e(k + 1, k, n)];

        double norm_a1 = sqrt(Sk + matrix[e(k, k, n)] * matrix[e(k, k, n)]);

        X[1] = matrix[e(k, k, n)] - norm_a1;
        X[2] = matrix[e(k + 1, k, n)];
        U1[k] = X[1];
        U2[k] = X[2];
    //    std::cout << k << " sk and x1 and x2 " << Sk << " " << X[1] << " " << X[2] <<  "\n";

        double norm_x = sqrt(Sk + X[1] * X[1]);

        if(norm_x > eps)
        {
            //вычислили искомый вектор х
            double B = 1 / norm_x;
            X[1] *= B;
            X[2] *= B;
            U1[k] = X[1];
            U2[k] = X[2];

            //умножаем исходную матрицу на матрицу отражения слева
            double scalar_prodact = 0;
            for(j = k; j < subn + 1; j++)
            {
                scalar_prodact = 0;
                for(i = k; i < k + 2; i++)
                    scalar_prodact += X[i - k + 1] * matrix[e(i, j, n)];
                scalar_prodact = -scalar_prodact;
                for(i = k; i < k + 2; i++)
                    matrix[e(i, j, n)] += 2 * X[i - k + 1] * scalar_prodact;
            }
        }
    }
}

void RQ(double *matrix, double *U1, double *U2, int n, int subn)
{
    double scalar_prodact = 0;
    for(int k = 1; k < subn; ++k)
    {
        for(int i = 1; i < subn + 1; i++)
        {
            scalar_prodact = U1[k] * matrix[e(i, k, n)] + U2[k] * matrix[e(i, k + 1, n)];
            scalar_prodact = -scalar_prodact;
            matrix[e(i, k, n)] += 2 * scalar_prodact * U1[k];
            matrix[e(i, k + 1, n)] += 2 * scalar_prodact * U2[k];
        }
    }
}

void QRshift(double *matrix, double *X, double *U1, double *U2, double *ans, int n, int subn, double eps, double MatrNormEps)
{
    int iteration = 0;
    while(iteration < 10000)
    {
        double sk = matrix[e(subn, subn, n)];
        for(int i = 1; i < subn + 1; ++i)
            matrix[e(i, i, n)] -= sk;

        QRdecomposition(matrix, X, U1, U2, n, subn, eps);
        RQ(matrix, U1, U2, n, subn);
        for(int i = 1; i < subn + 1; ++i)
            matrix[e(i, i, n)] += sk;

        if(abs(matrix[e(subn, subn - 1, n)]) < MatrNormEps)
        {
            ans[subn] = matrix[e(subn, subn, n)];
            return;
        }
        iteration++;
    }
}

int Eignvalues(double* matrix, double* X, double* U1, 
    double* U2, double* ans, int n, double epsans) 
{
    double max = norm(matrix, n);
    if(abs(max) < epsans) {
        for(int k = 1; k <= n; ++k) {
            ans[k] = 0;
        }
        return 1;
    }

    double MatrNormEps = epsans * fabs(max);
    double eps = max * 1e-10;
    int subn = n;

    ToAlmostDiagRefl(matrix, X, n, eps);
//    print(n, matrix, n);

    for(int k = 1; k < n; ++k) {
        max = norm(matrix, subn);
        MatrNormEps = epsans * fabs(max);
        eps = max * 1e-10;
        if (abs(max) < epsans)
        {
            for (int c = 1; c < subn; ++c)
                ans[c] = 0;

            return 1;
        }
        if(subn == 1) { ans[1] = matrix[e(1,1,n)]; return 1; }
        if(subn == 2) {
            double D = (matrix[e(1, 1, n)] - matrix[e(2, 2, n)])*(matrix[e(1, 1, n)] - matrix[e(2, 2, n)]) + 4*matrix[e(1, 2, n)]*matrix[e(2, 1, n)]; 
            if(D > epsans) {
                ans[1] = 0.5*(matrix[e(1, 1, n)] + matrix[e(2, 2, n)] + sqrt(D));
                ans[2] = ans[1] - sqrt(D);
                return 1;
            }
            if(D < epsans) return -3;
            else {
                ans[1] = 0.5*(matrix[e(1, 1, n)] + matrix[e(2, 2, n)]);
                ans[2] = ans[1];
                return 1;
            }
            return 1; 
            }
        QRshift(matrix, X, U1, U2, ans, n, subn, eps, MatrNormEps);
        subn--;
    }
    return -2;
}
