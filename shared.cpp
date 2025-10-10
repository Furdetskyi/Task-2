#include <stdio.h>
#include <omp.h>


int main() {
    int i, n = 5;
    int a[5] = {1, 2, 3, 4, 5};


    #pragma omp parallel for shared(a)
    for (i = 0; i < n; i++) {
        a[i] += i;
        printf("Thread %d changed a[%d] = %d\n",
               omp_get_thread_num(), i, a[i]);
    }


    printf("Final array: ");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}
