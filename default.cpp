#include <stdio.h>
#include <omp.h>


int main() {
    int i, n = 5;
    int a[5], b[5], c[5];


    for (i = 0; i < n; i++) {
        a[i] = i;
        b[i] = 2 * i;
    }


    #pragma omp parallel for default(shared) private(i)
    for (i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
        printf("Thread %d computes c[%d] = %d\n",
               omp_get_thread_num(), i, c[i]);
    }


    printf("Result: ");
    for (i = 0; i < n; i++)
        printf("%d ", c[i]);
    printf("\n");
    return 0;
}
