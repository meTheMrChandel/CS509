#include "../include/matrix.h"
#include <fstream>
#include <iostream>

// Helper to instantiate a 2D vector with dimensions i_rows x i_cols.
Matrix create_matrix(int i_rows, int i_cols)
{
    return Matrix(i_rows, std::vector<int>(i_cols, 0));
}

// Opens the specified file and parses matrix parameters and data values.
bool matrix_read(const std::string& str_filename, Matrix& mat_a, Matrix& mat_b, int& i_m, int& i_k, int& i_n)
{
    std::ifstream stream_fin(str_filename);

    // Make sure the file exists and is readable.
    if (!stream_fin.is_open())
    {
        std::cerr << "Error: Unable to open matrix file " << str_filename << std::endl;
        return false;
    }

    // Read dimensions: matrix A is i_m x i_k, matrix B is i_k x i_n.
    stream_fin >> i_m >> i_k >> i_n;

    // Resize matrix buffers to read elements correctly.
    mat_a = create_matrix(i_m, i_k);
    mat_b = create_matrix(i_k, i_n);

    // Extract row-major values for Matrix A.
    for (int i_row = 0; i_row < i_m; ++i_row)
    {
        for (int i_col = 0; i_col < i_k; ++i_col)
        {
            stream_fin >> mat_a[i_row][i_col];
        }
    }

    // Extract row-major values for Matrix B.
    for (int i_row = 0; i_row < i_k; ++i_row)
    {
        for (int i_col = 0; i_col < i_n; ++i_col)
        {
            stream_fin >> mat_b[i_row][i_col];
        }
    }

    stream_fin.close();
    return true;
}

// Output matrix values row by row to standard terminal output.
void print_matrix(const Matrix& mat_matrix)
{
    for (const auto& v_row : mat_matrix)
    {
        for (int i_val : v_row)
        {
            std::cout << i_val << " ";
        }
        std::cout << "\n";
    }
}
