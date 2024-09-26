#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime> 
#define NUM_POINTS 6000000  

int main() {
    int i, count = 0;
    double x, y, z, pi;

    srand(time(NULL));

    double start_total = omp_get_wtime();

    #pragma omp parallel
    {
        int local_count = 0;
        double start_thread = omp_get_wtime();

        #pragma omp for private(x, y, z)
        for (i = 0; i < NUM_POINTS; i++) {
        
            x = (double)rand() / RAND_MAX;
            y = (double)rand() / RAND_MAX;

            z = x * x + y * y;

          
            if (z <= 1) {
                local_count++;
            }
        }

        #pragma omp atomic
        count += local_count;

        double end_thread = omp_get_wtime();
        printf("Thread %d execution time: %f seconds\n", omp_get_thread_num(), end_thread - start_thread);
    }

    double end_total = omp_get_wtime();

    
    pi = (double)count / NUM_POINTS * 4.0;

    printf("Estimated value of Pi: %f\n", pi);
    printf("Total execution time: %f seconds\n", end_total - start_total);
    return 0;
}

// actual pi = 3.14159265359 
