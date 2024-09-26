#include <stdio.h>
#include <stdlib.h>
#include <omp.h>  
#include <ctime> 

#define NUM_POINTS 6000000 

int main() {
    int i, count = 0;
    double x, y, z, pi;

    srand(time(NULL));

   
    double start = omp_get_wtime();

    for (i = 0; i < NUM_POINTS; i++) {
      
        x = (double)rand() / RAND_MAX; // 214 million i.e 2^31-1
        y = (double)rand() / RAND_MAX;

        z = x * x + y * y;

      
        if (z <= 1) {
            count++;
        }
    }
    double end = omp_get_wtime();

    pi = (double)count / NUM_POINTS * 4.0;

    printf("Estimated value of Pi: %f\n", pi);
    printf("Total execution time: %f seconds\n", end - start);
    return 0;
}

// actual pi = 3.14159265359 