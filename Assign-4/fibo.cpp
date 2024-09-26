#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int fibonacci(int n) {
    if (n <= 1) return n;

    int x, y;
    #pragma omp parallel sections
    {
        #pragma omp section
        x = fibonacci(n - 1);

        #pragma omp section
        y = fibonacci(n - 2);
    }

    return x + y;
}

int main() {
    int n = 23; 
    int result;

    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        result = fibonacci(n);
    }

    double end_time = omp_get_wtime();
    printf("Fibonacci(%d) = %d\n", n, result);
    printf("Runtime: %f seconds\n", end_time - start_time);

    return 0;
}
