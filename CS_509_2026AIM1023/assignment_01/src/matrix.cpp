#include "../include/matrix.h"

#include <fstream>
#include <iostream>

Matrix createMatrix(int rows, int cols) {
    return Matrix(rows, std::vector<int>(cols, 0));
}

bool readMatrices(const std::string& filename,
                  Matrix& A,
                  Matrix& B,
                  int& M,
                  int& K,
                  int& N) {

    std::ifstream fin(filename);

    if (!fin.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return false;
    }

    // Read matrix dimensions
    fin >> M >> K >> N;

    // Create matrices
    A = createMatrix(M, K);
    B = createMatrix(K, N);

    // Read Matrix A
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            fin >> A[i][j];
        }
    }

    // Read Matrix B
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            fin >> B[i][j];
        }
    }

    fin.close();
    return true;
}

void printMatrix(const Matrix& matrix) {

    for (const auto& row : matrix) {

        for (int value : row) {
            std::cout << value << " ";
        }

        std::cout << std::endl;
    }
}