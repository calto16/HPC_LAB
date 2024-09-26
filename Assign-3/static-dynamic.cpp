#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define VECTOR_SIZE 200  
#define SCALAR 5        

void vector_addition_static(int chunk_size) {
    int vector[VECTOR_SIZE];
    double start_time, end_time;


    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = rand() % 100;
    }

  
    omp_set_schedule(omp_sched_static, chunk_size);

    
    start_time = omp_get_wtime();

    #pragma omp parallel for schedule(static)
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector[i] += SCALAR;
    }

   
    end_time = omp_get_wtime();


    printf("STATIC Schedule, Chunk Size: %d, Runtime: %f seconds\n", chunk_size, end_time - start_time);
}

void vector_addition_dynamic(int chunk_size) {
    int vector[VECTOR_SIZE];
    double start_time, end_time;

  
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = rand() % 100;
    }

   
    omp_set_schedule(omp_sched_dynamic, chunk_size);


    start_time = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector[i] += SCALAR;
    }

  
    end_time = omp_get_wtime();


    printf("DYNAMIC Schedule, Chunk Size: %d, Runtime: %f seconds\n", chunk_size, end_time - start_time);
}

void vector_addition_nowait() {
    int vector[VECTOR_SIZE];
    double start_time, end_time;

    
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = rand() % 100;
    }


    start_time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int i = 0; i < VECTOR_SIZE; i++) {
            vector[i] += SCALAR;
        }


        #pragma omp single
        {
            printf("Vector addition with nowait completed.\n");
        }
    }


    end_time = omp_get_wtime();


    printf("NOWAIT Clause, Runtime: %f seconds\n", end_time - start_time);
}

int main() {
    int chunk_sizes[] = {1, 10, 50, 100};  // Different chunk sizes to test
    int num_chunks = sizeof(chunk_sizes) / sizeof(chunk_sizes[0]);


    printf("Testing STATIC Scheduling:\n");
    for (int i = 0; i < num_chunks; i++) {
        vector_addition_static(chunk_sizes[i]);
    }

 
    printf("Testing DYNAMIC Scheduling:\n");
    for (int i = 0; i < num_chunks; i++) {
        vector_addition_dynamic(chunk_sizes[i]);
    }

   
    printf("Testing NOWAIT Clause:\n");
    vector_addition_nowait();

    return 0;
}
