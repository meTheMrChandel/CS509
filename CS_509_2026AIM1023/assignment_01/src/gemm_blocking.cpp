#include "../include/gemm.h"
#include <algorithm>

// Tiled/Blocked General Matrix Multiplication (GEMM) implementation.
// Divides the matrices into smaller blocks (tiles) of size i_block_size x i_block_size.
// This increases temporal locality by reusing data stored in the cache.
void gemm_blocking(const Matrix& mat_a, const Matrix& mat_b, Matrix& mat_c, int i_m, int i_k, int i_n, int i_block_size)
{
    // Handle invalid block sizes gracefully using a default value of 32.
    if (i_block_size <= 0)
    {
        i_block_size = 32;
    }

    // Initialize all values in the output matrix to zero.
    for (int i_row = 0; i_row < i_m; ++i_row)
    {
        for (int i_col = 0; i_col < i_n; ++i_col)
        {
            mat_c[i_row][i_col] = 0;
        }
    }

    // Outer loops iterate over the matrix tiles.
    for (int i_tile_row = 0; i_tile_row < i_m; i_tile_row += i_block_size)
    {
        for (int i_tile_col = 0; i_tile_col < i_n; i_tile_col += i_block_size)
        {
            for (int i_tile_idx = 0; i_tile_idx < i_k; i_tile_idx += i_block_size)
            {
                // Determine the boundaries for the current block (prevents index out-of-bounds).
                int i_row_limit = std::min(i_tile_row + i_block_size, i_m);
                int i_col_limit = std::min(i_tile_col + i_block_size, i_n);
                int i_idx_limit = std::min(i_tile_idx + i_block_size, i_k);

                // Inner loops perform standard matrix multiplication inside the sub-blocks/tiles.
                for (int i_row = i_tile_row; i_row < i_row_limit; ++i_row)
                {
                    for (int i_col = i_tile_col; i_col < i_col_limit; ++i_col)
                    {
                        int i_temp_sum = 0;
                        for (int i_idx = i_tile_idx; i_idx < i_idx_limit; ++i_idx)
                        {
                            i_temp_sum += mat_a[i_row][i_idx] * mat_b[i_idx][i_col];
                        }
                        mat_c[i_row][i_col] += i_temp_sum;
                    }
                }
            }
        }
    }
}
