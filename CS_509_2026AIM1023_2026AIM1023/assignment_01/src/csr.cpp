#include "../include/csr.h"

CSRGraph convertToCSR(const AdjList& graph)
{
    CSRGraph csr;

    int vertices = graph.size();

    csr.rowPtr.resize(vertices + 1);

    int edgeIndex = 0;

    for (int i = 0; i < vertices; i++)
    {
        csr.rowPtr[i] = edgeIndex;

        for (const Edge& edge : graph[i])
        {
            csr.colIndex.push_back(edge.destination);
            csr.weights.push_back(edge.weight);
            edgeIndex++;
        }
    }

    csr.rowPtr[vertices] = edgeIndex;

    return csr;
}