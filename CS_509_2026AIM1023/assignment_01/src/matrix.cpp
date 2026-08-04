#include "../include/matrix.h"

#include <fstream>
#include <iostream>

Matrix createMatrix(int rows, int cols) {
    return Matrix(rows, std::vector<int>(cols, 0));
}

bool readMatrices(const std::string& name,Matrix& A,Matrix& B,int& M,int& K,int& N) {

    std::ifstream fin(name);

    if (!fin.is_open()) {
        std::cout<<"\nUnable to Open file\n";
        return false;
    }

    //Dimension of Matrix
    fin >> M >> K >> N;

    // Create matrices
    A = createMatrix(M, K);
    B = createMatrix(K, N);

    // Matix A
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            fin >> A[i][j];
        }
    }

    //Matrix B
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            fin >> B[i][j];
        }
    }

    fin.close();
    return true;
}

void printMatrix(const Matrix& matrix) {

    for (auto row : matrix) {

        for (int value : row) {
            std::cout << value << " ";
        }

        std::cout << std::endl;
    }
}