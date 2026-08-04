#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>
//Acting as Matrix reading file 
using Matrix = std::vector<std::vector<int>>;


bool readMatrices(const std::string& filename,Matrix& A,Matrix& B,int& M, int& K, int& N);
Matrix createMatrix(int rows, int cols);
void printMatrix(const Matrix& matrix);

#endif