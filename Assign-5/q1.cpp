#include <stdio.h>
#include <omp.h>

int main() {
    const char* family_members[] = {"Tushar", "Minakshi", "Shrikant", "Tejas"};

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            printf("Thread %d: %s\n", omp_get_thread_num(), family_members[0]); 
        }

        #pragma omp section
        {
            printf("Thread %d: %s\n", omp_get_thread_num(), family_members[1]); 
        }

        #pragma omp section
        {
            printf("Thread %d: %s\n", omp_get_thread_num(), family_members[2]); 
        }

        #pragma omp section
        {
            printf("Thread %d: %s\n", omp_get_thread_num(), family_members[3]); 
        }
    }

    return 0;
}
