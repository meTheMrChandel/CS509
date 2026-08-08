#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include "graph_io.h"
#include <vector>

// Runs the Floyd-Warshall all-pairs shortest path algorithm.
// Returns true if a negative weight cycle is detected, false otherwise.
// The matrix v_matrix is updated in place with the all-pairs shortest distances.
bool run_floyd_warshall(int i_vertexCount, std::vector<std::vector<int>>& v_matrix);

#endif // FLOYD_WARSHALL_H
