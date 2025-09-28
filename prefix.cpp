#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Кожен процес має своє число (наприклад rank+1)
    int myValue = rank + 1;
    int prefixSum = 0;

    // Префіксна редукція (скан)
    MPI_Scan(&myValue, &prefixSum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    // Вивід результатів
    std::cout << "Process " << rank 
              << " -> myValue = " << myValue 
              << ", prefixSum = " << prefixSum << std::endl;

    MPI_Finalize();
    return 0;
}
