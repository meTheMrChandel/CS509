#include "../include/gemm.h"

#include <bits/stdc++.h>
// Matrix here is 2D vector as mentioned in matrix.h file
void gemmBlocking( Matrix& A, Matrix& B,Matrix& C,int M,int K,int N,int blockSize)
{
    //initialising the matrix with 0
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
        }
    }

    // starssen matrix multiplication
    for (int i = 0; i < M; i += blockSize) {
        for (int j = 0; j < N; j += blockSize) {
            for (int k = 0; k < K; k += blockSize) {

                int iLast = std::min(i + blockSize, M);
                int jLast = std::min(j + blockSize, N);
                int kLast = std::min(k + blockSize, K);

                for (int i1 = i; i1 < iLast; i1++) {
                    for (int j1 = j; j1 < jLast; j1++) {
                        for (int k1 = k; k1 < kLast; k1++) {
                            C[i1][j1] += A[i1][k1] * B[k1][j1];
                        }
                    }
                }
            }
        }
    }
}