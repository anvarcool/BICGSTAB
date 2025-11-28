#include <cassert>
#include <iomanip>
#include "algebra.h"


Vector::Vector() : values(nullptr), len(0) {}

Vector::Vector(int n) : len(n) {
    values = new double[len]();
}

Vector::Vector(const Vector& other) : len(other.len) {
    values = new double[len];
    for (int i = 0; i < len; i++)
        values[i] = other.values[i];
}

Vector::~Vector() {
    delete[] values;
}

int Vector::get_size() const {
    return len;
}

double* Vector::get_values() const {
    return values;
}

double& Vector::operator[](int i) {
    assert(i >= 0 && i < len);
    return values[i];
}

const double& Vector::operator[](int i) const {
    assert(i >= 0 && i < len);
    return values[i];
}

Vector& Vector::operator=(const Vector& v) {
    if (this == &v) return *this;

    delete[] values;

    len = v.len;
    values = new double[len];
    for (int i = 0; i < len; i++)
        values[i] = v.values[i];

    return *this;
}

Vector Vector::operator+(const Vector& v) const {
    assert(len == v.len && "Error! Vectors have different sizes");
    Vector res(len);
    for (int i = 0; i < len; i++)
        res[i] = values[i] + v.values[i];
    return res;
}

Vector Vector::operator-(const Vector& v) const {
    assert(len == v.len && "Error! Vectors have different sizes");
    Vector res(len);
    for (int i = 0; i < len; i++)
        res[i] = values[i] - v.values[i];
    return res;
}

double Vector::operator*(const Vector& v) const {
    assert(len == v.len && "Error! Vectors have different sizes");
    double res = 0.0;
    for (int i = 0; i < len; i++)
        res += values[i] * v.values[i];
    return res;
}

Vector operator*(double a, const Vector& v) {
    Vector res(v.len);
    for (int i = 0; i < v.len; i++)
        res[i] = a * v.values[i];
    return res;
}




Matrix::Matrix() : values(nullptr), n_cols(0), n_rows(0) {}

Matrix::Matrix(int n_cols, int n_rows)
    : n_cols(n_cols), n_rows(n_rows)
{
    values = new double[n_cols * n_rows]();
}

Matrix::Matrix(const Matrix& m)
    : n_cols(m.n_cols), n_rows(m.n_rows)
{
    values = new double[n_cols * n_rows];
    for (int i = 0; i < n_cols * n_rows; i++)
        values[i] = m.values[i];
}

Matrix::~Matrix() {
    delete[] values;
}

double* Matrix::get_values() const {
    return values;
}

int Matrix::get_n_cols() const {
    return n_cols;
}

int Matrix::get_n_rows() const {
    return n_rows;
}

double& Matrix::operator()(int i, int j) {
    assert(i >= 0 && i < n_rows);
    assert(j >= 0 && j < n_cols);
    return values[i * n_cols + j];
}

const double& Matrix::operator()(int i, int j) const {
    assert(i >= 0 && i < n_rows);
    assert(j >= 0 && j < n_cols);
    return values[i * n_cols + j];
}

Vector Matrix::operator*(const Vector& v) const {
    assert(n_cols == v.get_size() && "Error! Wrong shape of matrix and vector");

    Vector res(n_rows);
    for (int i = 0; i < n_rows; i++) {
        res[i] = 0;
        for (int j = 0; j < n_cols; j++) {
            res[i] += (*this)(i, j) * v[j];
        }
    }

    return res;
}

Matrix& Matrix::operator=(const Matrix& m) {
    if (this == &m) return *this;

    delete[] values;

    n_cols = m.n_cols;
    n_rows = m.n_rows;
    values = new double[n_cols * n_rows];
    for (int i = 0; i < n_cols * n_rows; i++)
        values[i] = m.values[i];

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "[";
    for (int i = 0; i < v.get_size(); ++i) {
        os << std::fixed << std::setprecision(3) << v[i];
        if (i != v.get_size() - 1) os << ", ";
    }
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    os << "[\n";
    for (int i = 0; i < m.get_n_rows(); ++i) {
        os << "  [";
        for (int j = 0; j < m.get_n_cols(); ++j) {
            os << std::fixed << std::setprecision(3) << m(i,j);
            if (j != m.get_n_cols() - 1) os << ", ";
        }
        os << "]";
        if (i != m.get_n_rows() - 1) os << ",";
        os << "\n";
    }
    os << "]";
    return os;
}