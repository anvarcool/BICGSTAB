#pragma once
#include <iostream>

class Vector {
private:
    double* values;
    int len;

public:
    Vector();
    Vector(int l);
    Vector(const Vector& v);  

    ~Vector();

    int get_size() const;
    double* get_values() const;

    Vector& operator=(const Vector& v);     
    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    double operator*(const Vector& v) const;

    double& operator[](int i);
    const double& operator[](int i) const; 

    friend Vector operator*(double a, const Vector& v);
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);
};


class Matrix {
private:
    double* values;
    int n_cols;
    int n_rows;

public:
    Matrix();
    Matrix(int n_cols, int n_rows);
    Matrix(const Matrix& m);   

    ~Matrix();

    int get_n_cols() const;
    int get_n_rows() const;
    double* get_values() const;
    
    Matrix& operator=(const Matrix& m);

    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;

    Vector operator*(const Vector& x) const;
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
};
