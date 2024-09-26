#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void matrix_addition(int size, int num_threads) {
    int **matrix_a, **matrix_b, **result;
    double start_time, end_time;

   
    matrix_a = (int **)malloc(size * sizeof(int *));
    matrix_b = (int **)malloc(size * sizeof(int *));
    result = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        matrix_a[i] = (int *)malloc(size * sizeof(int));
        matrix_b[i] = (int *)malloc(size * sizeof(int));
        result[i] = (int *)malloc(size * sizeof(int));
    }

    // dummy data
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix_a[i][j] = rand() % 100;
            matrix_b[i][j] = rand() % 100;
        }
    }

    omp_set_num_threads(num_threads);


    start_time = omp_get_wtime();

    // The #pragma omp parallel for collapse(2) directive parallelizes the 
    // matrix addition operation. The collapse(2) clause combines the two 
    // nested loops into a single loop for parallelization.
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = matrix_a[i][j] + matrix_b[i][j];
        }
    }


    end_time = omp_get_wtime();

  
    printf("Matrix size: %d x %d, Threads: %d, time: %f seconds\n", size, size, num_threads, end_time - start_time);

    // memory free karna hai
    for (int i = 0; i < size; i++) {
        free(matrix_a[i]);
        free(matrix_b[i]);
        free(result[i]);
    }
    free(matrix_a);
    free(matrix_b);
    free(result);
}

int main() {
    int size = 10000;       
    int num_threads = 2;  

    matrix_addition(size, num_threads);

    return 0;
}
