#ifndef G_H
#define G_H

#include "matrix.h"

// Brute Force Algo For Matrix Multiplication
void gemmSimple(Matrix& A,  Matrix& B, Matrix& C, int M, int K, int N);
// Optimised One for Matirx Multiplication
void gemmBlocking( Matrix& A, Matrix& B, Matrix& C, int M, int K,int N, int blockSize);

#endif