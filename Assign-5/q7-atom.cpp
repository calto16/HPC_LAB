#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000  // Size of the array

int main() {
    int arr[N];
    long long total_sum = 0;

    // Initialize the array
    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;  // Fill with numbers 1 to N
    }

    double start_time = omp_get_wtime();

    // Parallel region
    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < N; i++) {
            #pragma omp atomic
            total_sum += arr[i];
        }
    }

    double end_time = omp_get_wtime();
    printf("Atomic total sum = %lld\n", total_sum);
    printf("Atomic execution time = %f seconds.\n", end_time - start_time);
    return 0;
}
