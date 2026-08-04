#ifndef MX_H
#define MX_H

#include <vector>
#include <string>
//Using Matrix instead of writting 2d vector again and again

using Matrix = std::vector<std::vector<int>>;


bool matrixRead(const std::string& filename,Matrix& A,Matrix& B,int& M, int& K, int& N);
Matrix createMatrix(int rows, int cols);
void printMatrix(Matrix& matrix);

#endif