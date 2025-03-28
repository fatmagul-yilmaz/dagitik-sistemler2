#ifdef _MSC_VER
#pragma comment(lib, "msmpi.lib")
#include "C:/Program Files (x86)/Microsoft SDKs/MPI/Include/mpi.h"
#else
#include <mpi.h>
#endif

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 4  // Matris boyutu (NxN)
#define MASTER 0

void fill_matrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

void print_matrix(int matrix[N][N], const char* name) {
    printf("\n%s:\n", name);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    int world_size, world_rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int A[N][N], B[N][N], C[N][N];
    int local_C[N][N] = {0};
    
    if (world_rank == MASTER) {
        srand(time(NULL));
        fill_matrix(A);
        fill_matrix(B);
        print_matrix(A, "Matris A");
        print_matrix(B, "Matris B");
    }
    
    MPI_Bcast(B, N*N, MPI_INT, MASTER, MPI_COMM_WORLD);
    MPI_Scatter(A, N*N / world_size, MPI_INT, local_C, N*N / world_size, MPI_INT, MASTER, MPI_COMM_WORLD);
    
    #pragma omp parallel for
    for (int i = 0; i < N / world_size; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                local_C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    MPI_Gather(local_C, N*N / world_size, MPI_INT, C, N*N / world_size, MPI_INT, MASTER, MPI_COMM_WORLD);
    
    if (world_rank == MASTER) {
        print_matrix(C, "Sonuç Matrisi C");
    }
    
    MPI_Finalize();
    return 0;
}
