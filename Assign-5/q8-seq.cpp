#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000000

int main() {
    int *arr = (int *)malloc(N * sizeof(int));
    long long total_sum = 0;
    
    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;  
    }


    clock_t start_time = clock();

    for (int i = 0; i < N; i++) {
        total_sum += arr[i];
    }

    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Sequential total sum = %lld\n", total_sum);
    printf("Sequential execution time = %f seconds.\n", elapsed_time);

    free(arr);
    return 0;
}
