#include "../include/sssp.h"

#include <iostream>
#include <queue>
#include <vector>
#include <limits>

void dijkstra(const CSRGraph& graph, int source)
{
    int vertices = graph.rowPtr.size() - 1;

    std::vector<int> distance(vertices, std::numeric_limits<int>::max());

    using Node = std::pair<int, int>;
    std::priority_queue<
        Node,
        std::vector<Node>,
        std::greater<Node>
    > pq;

    distance[source] = 0;
    pq.push({0, source});

    while (!pq.empty())
    {
        int currentDistance = pq.top().first;
        int currentVertex = pq.top().second;

        pq.pop();

        if (currentDistance > distance[currentVertex])
            continue;

        for (int i = graph.rowPtr[currentVertex];
             i < graph.rowPtr[currentVertex + 1];
             i++)
        {
            int neighbour = graph.colIndex[i];
            int weight = graph.weights[i];

            if (distance[currentVertex] + weight < distance[neighbour])
            {
                distance[neighbour] = distance[currentVertex] + weight;

                pq.push({distance[neighbour], neighbour});
            }
        }
    }

    std::cout << "Shortest Distances\n";

    for (int i = 0; i < vertices; i++)
    {
        std::cout << source
                  << " -> "
                  << i
                  << " = ";

        if (distance[i] == std::numeric_limits<int>::max())
            std::cout << "INF";
        else
            std::cout << distance[i];

        std::cout << std::endl;
    }
}