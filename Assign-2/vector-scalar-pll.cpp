#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000000 

int main() {
    int i;
    double scalar = 5.0;
    double *vector = (double *)malloc(N * sizeof(double));

    for (i = 0; i < N; i++) {
        vector[i] = i * 1.0;
    }

    double start_total = omp_get_wtime();
    // set the number of threads to 4
    omp_set_num_threads(8);

    #pragma omp parallel
    {
        // double start_thread = omp_get_wtime();

        #pragma omp for
        for (i = 0; i < N; i++) {
            vector[i] += scalar;
        }

        // double end_thread = omp_get_wtime();
        // printf("Thread %d execution time: %f seconds\n", omp_get_thread_num(), end_thread - start_thread);
    }

    double end_total = omp_get_wtime();
    printf("Total execution time: %f seconds\n", end_total - start_total);

    free(vector);
    return 0;
}
