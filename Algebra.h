#include <iostream>

class Vector{
private:
    double* values_;
    int len_;

public:
    Vector();
    Vector(int l);
    Vector(int n, double values[]);
    Vector(const Vector& v);
    double* get_values() const;
    int get_size() const;
    Vector operator + (const Vector& v);
    Vector operator - (const Vector& v);
    double& operator [](int i) const;
    double operator *(const Vector& v);
    friend Vector operator *(double a, const Vector& v);
    ~Vector();
};

class Matrix{
private:
    double* values_;
    int n_cols_;
    int n_rows_;

public:
    Matrix();
    Matrix(int n_rows, int n_cols);
    double* get_values() const;
    int get_n_cols() const;
    int get_n_rows() const;
    double& operator()(int i, int j);
    Vector operator *(const Vector& v);
    ~Matrix();
};

