#include <iostream>
#include <limits>
#include "algebra.h"
#include "generate_system.h"
#include <mpi.h>
    


int main(int argc, char** argv) 
{
    MPI_Init(NULL, NULL);
    int world_size;
    int world_rank;

    int N = 1000;

    Matrix A;
    Vector b, x_true;

    generate_system(N, A, b, x_true);

    

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);


    MPI_Finalize();
}
