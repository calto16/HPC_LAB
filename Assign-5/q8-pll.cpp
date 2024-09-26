#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10000000  

int main() {
    int *arr = (int *)malloc(N * sizeof(int));
    long long total_sum = 0;
    
 
    for (int i = 0; i < N; i++) {
        arr[i] = i + 1; 
    }

    double start_time = omp_get_wtime();

    #pragma omp parallel for reduction(+:total_sum)
    for (int i = 0; i < N; i++) {
        total_sum += arr[i];
    }

    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;

    printf("Parallel total sum = %lld\n", total_sum);
    printf("Parallel execution time = %f seconds.\n", elapsed_time);

    free(arr);
    return 0;
}
