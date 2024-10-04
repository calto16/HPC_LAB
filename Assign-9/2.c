#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 200  
int main(int argc, char *argv[]) {
    int rank, size, i, j, k;
    double A[MATRIX_SIZE][MATRIX_SIZE], B[MATRIX_SIZE][MATRIX_SIZE], C[MATRIX_SIZE][MATRIX_SIZE];
    double local_A[MATRIX_SIZE][MATRIX_SIZE], local_C[MATRIX_SIZE][MATRIX_SIZE];
    double start_time, end_time;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int rows_per_process = MATRIX_SIZE / size;

    if (rank == 0) {
        for (i = 0; i < MATRIX_SIZE; i++) {
            for (j = 0; j < MATRIX_SIZE; j++) {
                A[i][j] = i + j;  
                B[i][j] = i * j;  
            }
        }
    }
    MPI_Bcast(B, MATRIX_SIZE * MATRIX_SIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(A, rows_per_process * MATRIX_SIZE, MPI_DOUBLE,
                local_A, rows_per_process * MATRIX_SIZE, MPI_DOUBLE,
                0, MPI_COMM_WORLD);
    start_time = MPI_Wtime();

    for (i = 0; i < rows_per_process; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            local_C[i][j] = 0.0;
        }
    }

    for (i = 0; i < rows_per_process; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            for (k = 0; k < MATRIX_SIZE; k++) {
                local_C[i][j] += local_A[i][k] * B[k][j];
            }
        }
    }

    MPI_Gather(local_C, rows_per_process * MATRIX_SIZE, MPI_DOUBLE,
               C, rows_per_process * MATRIX_SIZE, MPI_DOUBLE,
               0, MPI_COMM_WORLD);
    end_time = MPI_Wtime();

    if (rank == 0) {
        printf("Resultant matrix C:\n");
        // for (i = 0; i < MATRIX_SIZE; i++) {
        //     for (j = 0; j < MATRIX_SIZE; j++) {
        //         printf("%f ", C[i][j]);
        //     }
        //     printf("\n");
        // }
        printf("%f ", C);

        printf("Time taken: %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
