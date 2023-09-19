#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <string.h>

class Ln {
    private:
        int _N;
        double * _knots;
        double * _meanings;


    public:
        Ln(int N, double * knots, double * meanings);
        Ln(Ln &P);
        ~Ln();

        void print() const;
        double Phi(int i, double x) const;
        double calculate(double x) const;
};