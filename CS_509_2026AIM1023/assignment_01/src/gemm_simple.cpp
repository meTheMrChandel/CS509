#include "../include/gemm.h"

void gemmSimple(const Matrix& A,
                const Matrix& B,
                Matrix& C,
                int M,
                int K,
                int N)
{
    // Ensure the result matrix starts with zeros
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
        }
    }

    // Standard triple-loop matrix multiplication
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < K; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}