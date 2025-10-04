#include <iostream>
#include <omp.h>


int main() {
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int nthreads = omp_get_num_threads();
        #pragma omp critical
        std::cout << "Thread " << tid << " out of " << nthreads << " is running.\n";
    }


    std::cout << "Max threads according to OpenMP: " << omp_get_max_threads() << std::endl;
    return 0;
}
