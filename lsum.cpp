#include <mpi.h>
#include <iostream>
#include <vector>
#include <numeric> // для std::accumulate

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N = 16; // довжина вектора
    std::vector<int> fullArray;

    if (rank == 0) {
        // Ініціалізуємо вектор значеннями 1..N
        fullArray.resize(N);
        for (int i = 0; i < N; i++) fullArray[i] = i + 1;
    }

    // Кожен процес отримає N/size елементів
    int localSize = N / size;
    std::vector<int> localArray(localSize);

    // Розсилаємо частини вектора всім процесам
    MPI_Scatter(fullArray.data(), localSize, MPI_INT,
                localArray.data(), localSize, MPI_INT,
                0, MPI_COMM_WORLD);

    // Локальна сума
    int localSum = std::accumulate(localArray.begin(), localArray.end(), 0);

    // Збираємо суму з усіх процесів у 0
    int totalSum = 0;
    MPI_Reduce(&localSum, &totalSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        std::cout << "Total sum of array [1.." << N << "] = " << totalSum << std::endl;
    }

    MPI_Finalize();
    return 0;
}




