#include <stdio.h>
#include <omp.h>


int main() {
    int i, a = 0, n = 5;


    #pragma omp parallel for private(i) lastprivate(a)
    for (i = 0; i < n; i++) {
        a = i + 1;
        printf("Thread %d has a = %d for i = %d\n",
               omp_get_thread_num(), a, i);
    }


    printf("Value of a after parallel for: a = %d\n", a);
    return 0;
}
