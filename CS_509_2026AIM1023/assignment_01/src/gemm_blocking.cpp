#include "../include/gemm.h"

#include <algorithm>

void gemmBlocking(const Matrix& A,
                  const Matrix& B,
                  Matrix& C,
                  int M,
                  int K,
                  int N,
                  int blockSize)
{
    // Initialize result matrix
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
        }
    }

    // Blocked matrix multiplication
    for (int ii = 0; ii < M; ii += blockSize) {
        for (int jj = 0; jj < N; jj += blockSize) {
            for (int kk = 0; kk < K; kk += blockSize) {

                int iEnd = std::min(ii + blockSize, M);
                int jEnd = std::min(jj + blockSize, N);
                int kEnd = std::min(kk + blockSize, K);

                for (int i = ii; i < iEnd; i++) {
                    for (int j = jj; j < jEnd; j++) {
                        for (int k = kk; k < kEnd; k++) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
}