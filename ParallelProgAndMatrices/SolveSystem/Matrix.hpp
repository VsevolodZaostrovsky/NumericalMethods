#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <string.h>


#define e(i, j, n) ((i-1)*(n) + (j-1))

double f (int k, int n, int i, int j); //функция заполнения матрицы 

class Matrix {
    public:
        int _N;
        double * _value;


        Matrix(int N);
        Matrix(const Matrix &Ma);
        ~Matrix();

        void print() const;

        int fillFile(std::string filename);
	    int fillFormula(int k);
        long double norm();
};

void print(int n, double *M, double *b, int m);