#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000  

int main() {
    int arr[N];
    long long total_sum = 0;

    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;  
    }

    double start_time = omp_get_wtime();


    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < N; i++) {
            total_sum += arr[i];
        }
    }

    double end_time = omp_get_wtime();
    printf("Unsynchronized total sum = %lld\n", total_sum);
    printf("Unsynchronized execution time = %f seconds.\n", end_time - start_time);
    return 0;
}
