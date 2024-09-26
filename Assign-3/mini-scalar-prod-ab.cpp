#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <limits.h>

#define N 10  // Adjusted size for demonstration

void permutation(int *array, int start, int end, int *min_dot_product, int *vector_b, int *vector_a) {
    if (start == end) {
        int dot_product = 0;

        // The reduction clause accumulates the dot product values in parallel.
        #pragma omp parallel for reduction(+:dot_product)
        for (int i = 0; i < N; i++) {
            dot_product += vector_a[i] * vector_b[i];
        }

        #pragma omp critical
        {
            if (dot_product < *min_dot_product) {
                *min_dot_product = dot_product;
            }
        }
    } else {
        for (int i = start; i <= end; i++) {
       
            int temp = array[start];
            array[start] = array[i];
            array[i] = temp;

            permutation(array, start + 1, end, min_dot_product, vector_b, vector_a);

         
            temp = array[start];
            array[start] = array[i];
            array[i] = temp;
        }
    }
}

int main() {
    int vector_a[N], vector_b[N];
    int min_dot_product = INT_MAX;

  
    for (int i = 0; i < N; i++) {
        vector_a[i] = i;
        vector_b[i] = i;
    }

 
    int perm[N];
    for (int i = 0; i < N; i++) {
        perm[i] = i;
    }

    
    omp_set_num_threads(8);  


    double start = omp_get_wtime();

    permutation(perm, 0, N - 1, &min_dot_product, vector_b, vector_a);

    double end = omp_get_wtime();

    printf("Minimum scalar product: %d\n", min_dot_product);
    printf("Total execution time: %f seconds\n", end - start);

    return 0;
}
