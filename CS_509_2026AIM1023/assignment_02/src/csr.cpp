#include "../include/csr.h"

// Compressed Sparse Row (CSR) converter implementation.
// Flattens adjacency lists into three contiguous vectors for cache efficiency.
CSRGraph convert_to_csr(const AdjList& v_adjList)
{
    CSRGraph struct_csr;

    int i_vertexCount = static_cast<int>(v_adjList.size());

    // Allocate row pointer structure, size is V + 1.
    struct_csr.v_rowPtr.resize(i_vertexCount + 1);

    int i_edgeIdx = 0;

    // Process adjacency vectors for each vertex.
    for (int i_v = 0; i_v < i_vertexCount; ++i_v)
    {
        // Store current edge offset for this vertex.
        struct_csr.v_rowPtr[i_v] = i_edgeIdx;

        // Traverse all edges associated with vertex i_v.
        for (const Edge& struct_edge : v_adjList[i_v])
        {
            // Record target column index and weight values.
            struct_csr.v_colIndex.push_back(struct_edge.i_destination);
            struct_csr.v_edgeWeights.push_back(struct_edge.i_weight);
            i_edgeIdx++;
        }
    }

    // Set trailing row offset equal to total edges count (E).
    struct_csr.v_rowPtr[i_vertexCount] = i_edgeIdx;

    return struct_csr;
}
