#ifndef GEMM_H
#define GEMM_H

#include "matrix.h"

// Refactored Simple General Matrix Multiplication (GEMM) declaration.
// Uses type-prefixed snake_case for parameters.
void gemm_simple(const Matrix& mat_a, const Matrix& mat_b, Matrix& mat_c, int i_m, int i_k, int i_n);

// Refactored Cache-Blocking General Matrix Multiplication (GEMM) declaration.
// Uses type-prefixed snake_case for parameters.
void gemm_blocking(const Matrix& mat_a, const Matrix& mat_b, Matrix& mat_c, int i_m, int i_k, int i_n, int i_block_size);

#endif // GEMM_H
