#include <iostream>
#include <math.h>
#include <fstream>
#include "algebra.h"
#include "generate_system.h"
#include <mpi.h>

using namespace std;

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");

    MPI_Init(NULL, NULL);

    int world_size;
    int world_rank;

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int N = 20000;

    Matrix A;
    Vector b, x_true;

    if (world_rank == 0)
    {
        if (argc > 1 && string(argv[1]) == "-f"){
            ifstream in_mat("A.txt");
            ifstream in_vec("b.txt");
            in_mat >> A;
            in_mat.close();
            in_vec >> b;
            in_vec.close();
            N = A.get_n_cols();
            cout << "Got input from files";
        }
        else if (argc > 1 && string(argv[1]) == "-c"){
            cin >> A;
            cin >> b;
            N = A.get_n_cols();
            cout << "Got input from console";
        }
    }
    
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int block_counts[world_size], block_index[world_size];
    int block_counts_2d[world_size], block_index_2d[world_size];


    for(int i = 0; i < world_size; i++)
    {
        block_counts[i] = N / world_size;
        block_index[i] = block_counts[i] * i;

        block_counts_2d[i] = (N / world_size) * N;
        block_index_2d[i] = block_counts_2d[i] * i;
    }
    block_counts[world_size - 1] += N % world_size;
    block_counts_2d[world_size - 1] += (N % world_size) * N;

    Matrix A_loc(N, block_counts[world_rank]);
    Vector r, r_0, p(N), v(N), x(N);
    double rho, alpha, omega, epsilon;
    int max_iter, iter;
    char mode;
    rho = alpha = omega = 1;
    epsilon = 1e-6;
    max_iter = 10000;
    iter = 0;
    int continue_iteration = true;
    double time_start = MPI_Wtime();


    if (world_rank == 0)
    {
        if(argc == 1){
            generate_system(N, A, b, x_true);
            cout << "Generated system";
        }
        r = b - A * x;
        r_0 = r;
    }


    MPI_Scatterv(
        A.get_values(),
        block_counts_2d,
        block_index_2d,
        MPI_DOUBLE,
        A_loc.get_values(),
        block_counts_2d[world_rank],
        MPI_DOUBLE,
        0,
        MPI_COMM_WORLD
    );

    MPI_Barrier(MPI_COMM_WORLD);

    while(continue_iteration){
        iter += 1;
        double beta, rho_new;
        Vector v_loc;

        if(world_rank == 0)
        {
            rho_new = r_0 * r;
            beta = (rho_new / rho) * (alpha / omega);
            p = r + beta * (p - omega * v);
        }

        MPI_Bcast(p.get_values(), N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        v_loc = A_loc * p;

        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Gatherv(
            v_loc.get_values(),
            block_counts[world_rank],
            MPI_DOUBLE,
            v.get_values(),
            block_counts,
            block_index,
            MPI_DOUBLE,
            0,
            MPI_COMM_WORLD
        );

        Vector s(N), t_loc, t(N);

        if(world_rank == 0)
        {
            alpha = rho_new / (r_0 * v);
            s = r - alpha * v;
        }

        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Bcast(s.get_values(), N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        t_loc = A_loc * s;

        MPI_Gatherv(
            t_loc.get_values(),
            block_counts[world_rank],
            MPI_DOUBLE,
            t.get_values(),
            block_counts,
            block_index,
            MPI_DOUBLE,
            0,
            MPI_COMM_WORLD
        );

        if(world_rank == 0)
        {
            omega = (t * s) / (t * t);
            x = x + omega * s + alpha * p;
            r = s - omega * t;
            rho = rho_new;


            if ((r * r) / (b * b) < epsilon){
                continue_iteration = false;
            }

            if (iter >= max_iter){
                continue_iteration = false;
                cout << "Метод не сошелся за " << max_iter << "Итераций" << endl;
            }
        }


        MPI_Bcast(&continue_iteration, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }

    double time_end = MPI_Wtime();
    if (world_rank == 0)
    {
        double residual = sqrt(r * r) / sqrt(b * b);

        cout << "\n============================\n";
        cout << "  MPI BiCGStab completed\n";
        cout << "============================\n";
        cout << "System size             : " << N << endl;
        cout << "Number of processes     : " << world_size << endl;
        cout << "Accuracy epsilon        : " << epsilon << endl;
        cout << "Iterations              : " << iter << endl;
        cout << "Relative residual       : " << residual << endl;
        cout << "Execution time          : " << (time_end - time_start) << " sec\n";
        cout << "============================\n\n";
        ofstream out("result.txt");
        out << x;
        out.close();
    }


    MPI_Finalize();
}
