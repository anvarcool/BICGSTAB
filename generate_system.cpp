#include "generate_system.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

void generate_system(int N, Matrix &A, Vector &b, Vector &x_true) {
    static bool seeded = false;
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }

    A = Matrix(N, N);
    b = Vector(N);
    x_true = Vector(N);

    for (int i = 0; i < N; ++i)
        x_true[i] = (rand() % 1000) / 100.0;


    for (int i = 0; i < N; ++i) {
    double sum = 0.0;
    for (int j = 0; j < N; ++j) {
        if (i != j) {
            A(i,j) = (rand() % 10) / 2.0;
            sum += std::abs(A(i,j));
        }
    }
    A(i,i) = sum + 1.0;
}

    for (int i = 0; i < N; ++i) {
        double s = 0.0;
        for (int j = 0; j < N; ++j)
            s += A(i,j) * x_true[j];
        b[i] = s;
    }
}
