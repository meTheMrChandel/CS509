#include "../include/matrix.h"
#include "../include/gemm.h"
#include "../include/timer.h"

#include <iostream>

int main() {

    Matrix A, B, C;
    int M, K, N;

    std::string filename = "tests/gemm_test_01.txt";
    std::cout << "Reading file: " << filename << std::endl;
    if (!readMatrices(filename, A, B, M, K, N)) {
        return 1;
    }

    C = createMatrix(M, N);

    int choice;
    int blockSize = 0;

    std::cout << "=============================\n";
    std::cout << "      GEMM Simulator\n";
    std::cout << "=============================\n";
    std::cout << "1. Simple GEMM\n";
    std::cout << "2. Blocking GEMM\n";
    std::cout << "Enter Choice: ";
    std::cin >> choice;

    if (choice == 2) {
        std::cout << "Enter Block Size: ";
        std::cin >> blockSize;
    }

    // Start timing ONLY the algorithm
    TimePoint start = startTimer();

    switch (choice) {

        case 1:
            gemmSimple(A, B, C, M, K, N);
            break;

        case 2:
            gemmBlocking(A, B, C, M, K, N, blockSize);
            break;

        default:
            std::cout << "Invalid Choice\n";
            return 1;
    }

    double elapsedTime = stopTimer(start);

    std::cout << "\nResult Matrix\n";
    printMatrix(C);

    std::cout << "\nExecution Time : "
              << elapsedTime
              << " microseconds\n";

    return 0;
}