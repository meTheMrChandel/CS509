#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <vector>

// Matrix type alias representing a 2D integer vector.
using Matrix = std::vector<std::vector<int>>;

// Create a matrix of size i_rows x i_cols initialized to 0.
Matrix create_matrix(int i_rows, int i_cols);

// Read matrix data from input file. Sets dimensions and loads content.
bool matrix_read(const std::string& str_filename, Matrix& mat_a, Matrix& mat_b, int& i_m, int& i_k, int& i_n);

// Print matrix rows and columns to stdout.
void print_matrix(const Matrix& mat_matrix);

#endif // MATRIX_H
