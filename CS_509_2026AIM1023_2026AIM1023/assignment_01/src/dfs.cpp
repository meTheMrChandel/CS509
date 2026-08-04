#include "../include/dfs.h"

#include <iostream>
#include <vector>

void dfsHelper(const CSRGraph& graph,
               int current,
               std::vector<bool>& visited)
{
    visited[current] = true;

    std::cout << current << " ";

    for (int i = graph.rowPtr[current];
         i < graph.rowPtr[current + 1];
         i++)
    {
        int neighbour = graph.colIndex[i];

        if (!visited[neighbour])
        {
            dfsHelper(graph, neighbour, visited);
        }
    }
}

void dfs(const CSRGraph& graph, int source)
{
    int vertices = graph.rowPtr.size() - 1;

    std::vector<bool> visited(vertices, false);

    std::cout << "DFS Traversal: ";

    dfsHelper(graph, source, visited);

    std::cout << std::endl;
}