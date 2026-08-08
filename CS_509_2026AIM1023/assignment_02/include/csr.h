#ifndef CSR_H
#define CSR_H

#include <vector>

// Struct representing a graph edge.
struct Edge
{
    int i_destination; // Destination vertex ID.
    int i_weight;      // Edge weight (can be negative).
};

// Type alias representing adjacency list structure.
using AdjList = std::vector<std::vector<Edge>>;

// Struct container holding all read parameters of the graph.
struct GraphInput
{
    AdjList v_adjList;     // Adjacency list representation.
    int i_vertexCount;     // Total vertex count (V).
    int i_edgeCount;       // Total edge count (E).
    int i_source;          // Specified source vertex for Bellman-Ford.
};

// Struct representing the Compressed Sparse Row (CSR) format graph.
struct CSRGraph
{
    std::vector<int> v_rowPtr;      // Row offsets. Size: V + 1.
    std::vector<int> v_colIndex;    // Destination vertex indices. Size: E.
    std::vector<int> v_edgeWeights; // Edge weights. Size: E.
};

// Converts standard Adjacency List to CSR representation.
CSRGraph convert_to_csr(const AdjList& v_adjList);

#endif // CSR_H
