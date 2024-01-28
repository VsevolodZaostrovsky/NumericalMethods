#pragma once
#include "Matrix.hpp"

class vector
{
public:
    double* vector_;
    int d_;

    vector(int dim);
    vector(vector &v);
    vector(Matrix &m);
    ~vector();

    vector& operator=(const vector &v);
    void print(int m);
    double norm();
    friend vector operator+(const vector &v1, const vector &v2);
    friend vector operator-(const vector &v1, const vector &v2);
};

vector operator*(const Matrix &m, const vector &v);


