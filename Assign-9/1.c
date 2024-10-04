#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 700

int main(int argc, char *argv[]) {
    int rank, size, i, j;
    double matrix[MATRIX_SIZE][MATRIX_SIZE];
    double vector[MATRIX_SIZE];
    double local_result[MATRIX_SIZE], result[MATRIX_SIZE];
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rows_per_process = MATRIX_SIZE / size;  


    if (rank == 0) {

        for (i = 0; i < MATRIX_SIZE; i++) {
            vector[i] = 1; 
            for (j = 0; j < MATRIX_SIZE; j++) {
                matrix[i][j] = i + j;  
            }
        }
    }


    double local_matrix[rows_per_process][MATRIX_SIZE];
    MPI_Scatter(matrix, rows_per_process * MATRIX_SIZE, MPI_DOUBLE,
                local_matrix, rows_per_process * MATRIX_SIZE, MPI_DOUBLE,
                0, MPI_COMM_WORLD);


    MPI_Bcast(vector, MATRIX_SIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);


    start_time = MPI_Wtime();


    for (i = 0; i < rows_per_process; i++) {
        local_result[i] = 0.0;
        for (j = 0; j < MATRIX_SIZE; j++) {
            local_result[i] += local_matrix[i][j] * vector[j];
        }
    }


    MPI_Gather(local_result, rows_per_process, MPI_DOUBLE,
               result, rows_per_process, MPI_DOUBLE,
               0, MPI_COMM_WORLD);


    end_time = MPI_Wtime();

    if (rank == 0) {
        printf("Resultant vector:\n");
        // for (i = 0; i < MATRIX_SIZE; i++)
        //     printf("%f ", result[i]);
        printf("%f ", result);
        printf("\n");

        printf("Time taken: %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
