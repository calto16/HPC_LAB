#include <stdio.h>
#include <stdlib.h>
#include <omp.h>  

#define N 1000000  

int main() {
    int i;
    double scalar = 5.0;
    double *vector = (double *)malloc(N * sizeof(double));

    for (i = 0; i < N; i++) {
        vector[i] = i * 1.0;
    }

    
    double start = omp_get_wtime();

    for (i = 0; i < N; i++) {
        vector[i] += scalar;
    }

    double end = omp_get_wtime();
    printf("Total execution time: %f seconds\n", end - start);

    free(vector);
    return 0;
}
