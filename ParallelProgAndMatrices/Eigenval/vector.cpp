#include "vector.hpp"

vector::vector(int dim)
{
    if(dim <= 0) 
    {
        throw "vector::vector - incorrect dim";
    }
    d_ = dim;
    vector_ = new double[dim];
}

vector::vector(vector &v)
{
    d_ = v.d_;
    vector_ = new double[d_];
    for (int i = 0; i < d_; i++)
    {
        vector_[i] = v.vector_[i];
    }
}

vector::vector(Matrix &m)
{
    vector_ = new double[m._N];
    d_ = m._N;
    for (int i = 1; i < m._N + 1; i++)
    {
        double sum = 0;
        for (int j = 1; j < m._N + 1; j += 2)
        {
            sum += m._value[e(i, j, m._N)];
        }
        vector_[i - 1] = sum;
    }
}

vector::~vector()
{
    delete[] vector_;
    d_ = 0;
}

vector &vector::operator=(const vector &v)
{
    if(this == &v) 
    {
        return *this;
    }
    this->d_ = v.d_;
    delete[] this->vector_;
    this->vector_ = new double[this->d_];
    for (int i = 0; i < d_; i++)
    {
        this->vector_[i] = v.vector_[i];
    }
    return *this;
}

vector operator+(const vector &v1, const vector &v2)
{
    if (v1.d_ != v2.d_)
    {
        throw "vector::+ bad params";
    }
    vector res(v1.d_);
    for (int i = 0; i < v1.d_; i++)
    {
        res.vector_[i] = v1.vector_[i] + v2.vector_[i];
    }

    return res;
}

vector operator-(const vector &v1, const vector &v2)
{
    if (v1.d_ != v2.d_)
    {
        throw "vector::- bad params";
    }
    vector res(v1.d_);
    for (int i = 0; i < v1.d_; i++)
    {
        res.vector_[i] = v1.vector_[i] - v2.vector_[i];
    }

    return res;
}

double vector::norm()
{
    double nrm = 0;
    for (int i = 1; i <= d_; i++)
    {
        nrm += abs(vector_[i - 1]);
    }
    return nrm;
}

vector operator*(const Matrix &m, const vector &v)
{
    if (m._N != v.d_)
    {
        throw "Matrix*vector bad params";
    }
    vector res(m._N);

    for (int i = 1; i <= m._N; i++)
    {
        double t = 0;
        for (int j = 1; j <= m._N; j++)
        {
            t += m._value[e(i, j, m._N)] * v.vector_[j - 1];
        }
        res.vector_[i - 1] = t;
    }
    return res;
}

void vector::print(int m) {
    std::cout << "(";
    for(int k = 0; k < d_ - 1; ++k) {
        if(k < m - 1)
        {
        std::cout << vector_[k] << " ";
        }
    }
    if(m < d_) { std::cout << " ... "; }
    std::cout << vector_[d_-1] << ")\n"; 
}

