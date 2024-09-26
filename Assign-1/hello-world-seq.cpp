#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    printf("thread No. %d  Hello World\n", omp_get_thread_num());

    return 0;
}

// FLOPS=Number of cores × Clock speed (GHz) × Number of FLOPs per cycle    
// FLOPS=4 × 2.4 × 8 = 76.8 GFLOPS