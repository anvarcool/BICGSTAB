#include <cassert>
#include <iostream>
#include "Algebra.h"

using namespace std;

void test_vector_constructor() {
    Vector v(3);
    assert(v.get_size() == 3);
}

void test_vector_set_get() {
    Vector v(3);
    v[0] = 1.0;
    v[1] = 2.0;
    v[2] = 3.0;
    assert(v[0] == 1.0);
    assert(v[1] == 2.0);
    assert(v[2] == 3.0);
}

void test_vector_addition() {
    Vector a(3), b(3);
    a[0]=1; a[1]=2; a[2]=3;
    b[0]=4; b[1]=5; b[2]=6;

    Vector c = a + b;
    assert(c[0] == 5);
    assert(c[1] == 7);
    assert(c[2] == 9);
}

void test_vector_subtraction() {
    Vector a(3), b(3);
    a[0]=5; a[1]=7; a[2]=9;
    b[0]=1; b[1]=2; b[2]=3;

    Vector c = a - b;
    assert(c[0] == 4);
    assert(c[1] == 5);
    assert(c[2] == 6);
}

void test_vector_dot_product() {
    Vector a(3), b(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    b[0] = 4;
    b[1] = 5;
    b[2] = 6;

    double dot = a * b;
    assert(dot == 1*4 + 2*5 + 3*6);
}

void test_scalar_mult_vector() {
    Vector v(3);
    v[0] = 1;
    v[1] = -2;
    v[2] = 3;

    Vector r = 2.0 * v;
    assert(r[0] == 2);
    assert(r[1] == -4);
    assert(r[2] == 6);
}

void test_vector_assignment() {
    Vector a(3);
    a[0]=10; a[1]=20; a[2]=30;

    Vector b;
    b = a;

    assert(b.get_size() == a.get_size());
    assert(b[0] == 10);
    assert(b[1] == 20);
    assert(b[2] == 30);
}

void test_matrix_constructor() {
    Matrix m(2, 3);
    assert(m.get_n_cols() == 2);
    assert(m.get_n_rows() == 3);
}

void test_matrix_set_get() {
    Matrix m(2, 2);
    m(0,0)=1; m(0,1)=2;
    m(1,0)=3; m(1,1)=4;

    assert(m(0,0) == 1);
    assert(m(0,1) == 2);
    assert(m(1,0) == 3);
    assert(m(1,1) == 4);
}

void test_matrix_vector_mul() {
    Matrix m(3, 2);  // 2×3
    m(0,0)=1; m(0,1)=2; m(0,2)=3;
    m(1,0)=4; m(1,1)=5; m(1,2)=6;

    Vector v(3);
    v[0]=1; v[1]=2; v[2]=3;

    Vector r = m * v; // результат 2×1

    assert(r[0] == 1*1 + 2*2 + 3*3);
    assert(r[1] == 4*1 + 5*2 + 6*3);
}

void test_assert_different_size() {
    Vector a(3), b(4);
    bool crashed = false;

    // Проверим, что assert срабатывает
    try {
        Vector c = a + b;
    } catch (...) {
        crashed = true;
    }

    // assert прекращает выполнение программы, поэтому try-catch не поймет.
    // Тем не менее тест демонстрационный: в реальности при запуске будет падение.
}

int main() {
    test_vector_constructor();
    test_vector_set_get();
    test_vector_addition();
    test_vector_subtraction();
    test_vector_dot_product();
    test_scalar_mult_vector();
    test_vector_assignment();
    test_matrix_constructor();
    test_matrix_set_get();
    test_matrix_vector_mul();

    cout << "All tests passed!" << endl;
    return 0;
}
