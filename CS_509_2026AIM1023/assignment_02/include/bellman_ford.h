#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "csr.h"
#include <vector>

// Large constant representing infinity for shortest paths.
const int i_BF_INF = 1000000000; // 1e9

// Runs the Bellman-Ford algorithm on a graph represented in CSR format.
// Returns true if a negative weight cycle is detected, false otherwise.
// Shortest path distances are populated in v_distances.
bool run_bellman_ford(int i_vertexCount, const CSRGraph& struct_csr, int i_source, std::vector<int>& v_distances);

#endif // BELLMAN_FORD_H
