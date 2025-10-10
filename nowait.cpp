#include <stdio.h>
#include <omp.h>


int main() {
    int i, n = 6;
    int a[6];


    #pragma omp parallel
    {
        #pragma omp for nowait
        for (i = 0; i < n; i++) {
            a[i] = i * 2;
            printf("Thread %d sets a[%d] = %d\n",
                   omp_get_thread_num(), i, a[i]);
        }


        // Потоки можуть продовжити виконання без бар’єра
        #pragma omp single
        {
            printf("Single section executed by thread %d\n",
                   omp_get_thread_num());
        }
    }


    printf("Final array: ");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}
