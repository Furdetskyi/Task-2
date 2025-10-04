#include <iostream>
#include <omp.h>


int main() {
#ifdef _OPENMP
    std::cout << "OpenMP version: " << _OPENMP << std::endl;
#else
    std::cout << "OpenMP is not supported." << std::endl;
#endif
    return 0;
}
