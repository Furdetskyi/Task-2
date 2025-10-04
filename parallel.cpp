#include <stdio.h>
#include <omp.h>


int main() {
    printf("Serial scope 1\n");


    #pragma omp parallel
    {
        printf("Parallel scope executed by thread %d\n", omp_get_thread_num());
    }


    printf("Serial scope 2\n");
    return 0;
}
