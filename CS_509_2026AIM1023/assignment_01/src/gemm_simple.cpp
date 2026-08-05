#include "../include/gemm.h"

// Standard General Matrix Multiplication (GEMM) implementation.
// This executes the baseline O(M * K * N) matrix multiplication algorithm
// using simple nested loops.
void gemm_simple(const Matrix& mat_a, const Matrix& mat_b, Matrix& mat_c, int i_m, int i_k, int i_n)
{
    // Initialize the destination matrix values to zero.
    for (int i_row = 0; i_row < i_m; ++i_row)
    {
        for (int i_col = 0; i_col < i_n; ++i_col)
        {
            mat_c[i_row][i_col] = 0;
        }
    }

    // Multiply matrices A and B using standard triple-nested loops.
    // mat_a is accessed sequentially along rows, but mat_b is accessed
    // stride-wise down its columns, causing cache misses for large matrix scales.
    for (int i_row = 0; i_row < i_m; ++i_row)
    {
        for (int i_col = 0; i_col < i_n; ++i_col)
        {
            int i_sum = 0;
            for (int i_idx = 0; i_idx < i_k; ++i_idx)
            {
                i_sum += mat_a[i_row][i_idx] * mat_b[i_idx][i_col];
            }
            mat_c[i_row][i_col] = i_sum;
        }
    }
}
