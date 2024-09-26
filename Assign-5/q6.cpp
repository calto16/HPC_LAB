#include <omp.h>
#include <stdio.h>

#define N 5

void print_series_2() {
    for (int i = 1; i <= N; i++) {
        printf("2 ");
    }
    printf("\n");
}

void print_series_4() {
    for (int i = 1; i <= N; i++) {
        printf("4 ");
    }
    printf("\n");
}

int main() {
  
    omp_set_num_threads(2);
    #pragma omp parallel
    {
      
        int thread_id = omp_get_thread_num();
        if (thread_id == 0) {
            printf("Thread No: %d\n", thread_id);
            print_series_2();
        } else if (thread_id == 1) {
            printf("Thread No: %d\n", thread_id);
            print_series_4();
        }
    }
    return 0;
}
