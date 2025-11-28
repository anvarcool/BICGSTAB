#include <iostream>
#include <assert.h>
#include "Algebra.h"

using namespace std;
Vector::Vector(): values_(nullptr), len_(0)
{}

Vector::Vector(int n): len_(n)
{
    values_ = new double[len_];
}

Vector::Vector(int n, double* values):
    len_(n)
{
    values_ = new double[len_];
    for (int i = 0; i < len_; i++)
        values_[i] = values[i];

}
Vector::Vector(const Vector& v): len_(v.get_size()){
    values_ = new double[len_];
    for (int i = 0; i < len_; i++){
        values_[i] = v[i];
    }
}

double* Vector::get_values() const{
        return values_;
}

int Vector::get_size() const{
        return len_;
}

double& Vector::operator [](int i) const{
    return values_[i];
}

Vector Vector::operator +(const Vector& v){
    assert(len_ == v.get_size() && "Error! Vectors have different sizes");
    Vector res(len_);
    for (int i = 0; i < len_; i++)
            res[i] = (*this)[i] + v[i];
    return res;
}

Vector Vector::operator -(const Vector& v){
    assert(len_ == v.get_size() && "Error! Vectors have different sizes");
    Vector res(len_);
    for (int i = 0; i < len_; i++)
            res[i] = (*this)[i] - v[i];
    return res;
}

double Vector::operator *(const Vector& v){
    double res = 0;
    assert(len_ == v.get_size() && "Error! Vectors have different sizes");
    for (int i = 0; i < len_; i++)
            res += (*this)[i] * v[i];
    return res;
}

Vector operator *(double a, const Vector& v){
    int len;
    len = v.get_size();
    Vector res(len);
    for (int i = 0; i < len; i++)
            res[i] = a * v[i];
    return res;
}



Matrix::Matrix(): values_(nullptr), n_cols_(0), n_rows_(0)
{}

Matrix::Matrix(int n_cols, int n_rows): n_cols_(n_cols), n_rows_(n_rows)
{
    values_ = new double[n_cols * n_rows];
}

double* Matrix::get_values() const{
    return values_;
}

int Matrix::get_n_cols() const{
    return n_cols_;
}
int Matrix::get_n_rows() const{
    return n_rows_;
}

double& Matrix::operator()(int i, int j){
    return *(values_ + n_cols_ * i + j);
}

Vector Matrix::operator *(const Vector& v){
    assert(n_cols_ == v.get_size() && "Error! Wrong shape of matrix and vector");
    Vector res(v.get_size());
    for (int i = 0; i < n_rows_; i++){
        res[i] = 0;
        for (int j = 0; j < n_cols_; j++)
            res[i] += (*this)(i, j) * v[j];
    }
    return res;
}
Vector::~Vector(){
    delete[] values_;
}

Matrix::~Matrix(){
    delete[] values_;
}

int main(){
    Vector a(5);
    Vector c(5);
    a[0] = 5;
    c[0] = -1;
    Vector b = Vector(a);
    cout << a[0] << ' ' << b[0] << ' ' << c[0] << endl;
    b[0] = 10;
    cout << a[0] << ' ' << b[0] << ' ' << c[0] << endl;
    b = Vector(c);
    cout << a[0] << ' ' << b[0] << ' ' << c[0] << endl;
}


