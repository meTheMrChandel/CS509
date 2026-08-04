#include "../include/bfs.h"

#include <iostream>
#include <queue>
#include <vector>

void bfs(const CSRGraph& graph, int source)
{
    int vertices = graph.rowPtr.size() - 1;

    std::vector<bool> visited(vertices, false);
    std::queue<int> q;

    visited[source] = true;
    q.push(source);

    std::cout << "BFS Traversal: ";

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        std::cout << current << " ";

        for (int i = graph.rowPtr[current];
             i < graph.rowPtr[current + 1];
             i++)
        {
            int neighbour = graph.colIndex[i];

            if (!visited[neighbour])
            {
                visited[neighbour] = true;
                q.push(neighbour);
            }
        }
    }

    std::cout << std::endl;
}