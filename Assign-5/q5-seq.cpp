#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 1000

int A[N][N];
int B[N][N];
int C[N][N];

void initialize_matrices() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = 2;
            B[i][j] = 2;
            C[i][j] = 0;  
        }
    }
}

void matrix_multiply_sequential() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    double total_time = 0;
    struct timeval tv1, tv2;
    struct timezone tz;

    initialize_matrices();
    gettimeofday(&tv1, &tz);
    matrix_multiply_sequential();
    gettimeofday(&tv2, &tz);
    double elapsed = (double) (tv2.tv_sec - tv1.tv_sec) + (double) (tv2.tv_usec - tv1.tv_usec) * 1.e-6;
    printf("Sequential scheduling elapsed time = %f seconds.\n", elapsed);

    return 0;
}
