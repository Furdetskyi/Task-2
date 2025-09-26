#include <mpi.h>
#include <iostream>
#include <vector>
#include <iomanip> // для std::setw

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // ===== ЧАСТИНА 1: Паралельна сума чисел =====
    int totalNumbers = 1000;
    int numbersPerProc = totalNumbers / size;

    int start = 1 + rank * numbersPerProc;
    int end = (rank == size - 1) ? totalNumbers : (rank + 1) * numbersPerProc; // останній процес бере залишок

    int localSum = 0;

    double t0 = MPI_Wtime(); // Початок вимірювання часу паралельного розрахунку

    for (int i = start; i <= end; ++i)
        localSum += i;

    // Вивід локальної інформації кожного процесу
    std::cout << "Process " << std::setw(2) << rank 
              << " -> range: [" << start << "-" << end 
              << "], local sum = " << localSum << std::endl;

    int totalSum = 0;
    if (rank != 0) {
        MPI_Send(&localSum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        totalSum = localSum;
        for (int i = 1; i < size; ++i) {
            int tmp;
            MPI_Recv(&tmp, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            totalSum += tmp;
        }
        double t1 = MPI_Wtime(); // Кінець вимірювання часу паралельного розрахунку
        std::cout << "\n=== Parallel Sum on Process 0 ===" << std::endl;
        std::cout << "Total sum from 1 to " << totalNumbers << " is: " << totalSum << std::endl;
        std::cout << "Execution time (all processes included): " << t1 - t0 << " seconds" << std::endl;
    }

    MPI_Barrier(MPI_COMM_WORLD); // синхронізація перед наступною частиною

    // ===== ЧАСТИНА 2: Передача масивів на процес 0 =====
    int N = 5; // розмір локального масиву на кожному процесі
    std::vector<int> localArray(N);

    for(int i = 0; i < N; ++i)
        localArray[i] = rank * N + i + 1; // унікальні значення

    if(rank != 0) {
        MPI_Send(localArray.data(), N, MPI_INT, 0, 1, MPI_COMM_WORLD);
    } else {
        std::vector<int> totalArray(N * size);
        for(int i = 0; i < N; ++i)
            totalArray[i] = localArray[i];

        for(int src = 1; src < size; ++src) {
            MPI_Recv(&totalArray[src*N], N, MPI_INT, src, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        std::cout << "\n=== Combined Array on Process 0 ===" << std::endl;
        for(int i = 0; i < totalArray.size(); ++i) {
            std::cout << std::setw(3) << totalArray[i] << " ";
            if ((i+1) % 10 == 0) std::cout << std::endl; // форматований вивід по 10 чисел у рядок
        }
        std::cout << std::endl;
    }

    MPI_Finalize();
    return 0;
}

