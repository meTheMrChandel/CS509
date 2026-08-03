#ifndef GEMM_H
#define GEMM_H

#include "matrix.h"

// Simple matrix multiplication
void gemmSimple(const Matrix& A,
                const Matrix& B,
                Matrix& C,
                int M,
                int K,
                int N);

// Blocking matrix multiplication
void gemmBlocking(const Matrix& A,
                  const Matrix& B,
                  Matrix& C,
                  int M,
                  int K,
                  int N,
                  int blockSize);

#endif