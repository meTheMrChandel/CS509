#ifndef GRAPH_IO_H
#define GRAPH_IO_H

#include "csr.h"
#include <string>
#include <vector>

// Representation of infinity for Floyd-Warshall dense matrix.
const int i_INF_VAL = 1000000000; // 1e9

// Reads a directed weighted graph for Bellman-Ford from file.
bool read_directed_weighted_graph(const std::string& str_fileName, GraphInput& struct_input);

// Reads a dense matrix for Floyd-Warshall from file.
// Returns a 2D matrix of size V x V, where INF is represented by i_INF_VAL.
bool read_adjacency_matrix(const std::string& str_fileName, int& i_vertexCount, std::vector<std::vector<int>>& v_matrix);

#endif // GRAPH_IO_H
