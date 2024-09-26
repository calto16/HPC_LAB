#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int n = 10; 
    int A[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 
    int local_sum = 0;

    if (world_rank == 0) {
     
        for (int i = 0; i < n / 2; i++) {
            local_sum += A[i];
        }
    } else if (world_rank == 1) {
    
        for (int i = n / 2; i < n; i++) {
            local_sum += A[i];
        }
    }
    int global_sum = 0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        printf("The total sum of the array is: %d\n", global_sum);
    }

    MPI_Finalize();
    return 0;
}
