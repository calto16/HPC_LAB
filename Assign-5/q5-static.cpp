#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 1000

int A[N][N];
int B[N][N];
int C[N][N];

int main() {
    int i, j, k;
    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed; 

    omp_set_num_threads(omp_get_num_procs());

 
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = 2;
            B[i][j] = 2;
            C[i][j] = 0;  
        }
    }

    gettimeofday(&tv1, &tz);

    #pragma omp parallel for schedule(static) private(i, j, k) shared(A, B, C)
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            int sum = 0;
            for (k = 0; k < N; ++k) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }

    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec - tv1.tv_sec) + (double) (tv2.tv_usec - tv1.tv_usec) * 1.e-6;
    printf("Static scheduling elapsed time = %f seconds.\n", elapsed);

    return 0;
}
