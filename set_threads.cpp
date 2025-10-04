#include <stdio.h>
#include <omp.h>


int main() {
    omp_set_dynamic(0);           // Вимикаємо динамічне керування
    omp_set_num_threads(8);       // Встановлюємо 8 потоків


    #pragma omp parallel
    {
        printf("Thread %d out of %d is working\n",
               omp_get_thread_num(), omp_get_num_threads());
    }
    return 0;
}
