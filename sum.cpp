#include <stdio.h>
#include <omp.h>


int main() {
    int n = 10;
    int a[10];
    int sum = 0;


    for (int i = 0; i < n; i++) a[i] = i + 1;


    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += a[i];
        printf("Thread %d adds %d\n", omp_get_thread_num(), a[i]);
    }


    printf("Total sum = %d\n", sum);
    return 0;
}
