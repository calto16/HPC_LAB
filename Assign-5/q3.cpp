#include <stdio.h>
#include <omp.h>

int main() {
    


    #pragma omp parallel 
    {
        int thread_id = omp_get_thread_num(); 
        int Aryabhatta = 10; 
        int result = thread_id * Aryabhatta;  

        printf("Thread %d: %d * %d = %d\n", thread_id, thread_id, Aryabhatta, result);
    }

    return 0;
}
