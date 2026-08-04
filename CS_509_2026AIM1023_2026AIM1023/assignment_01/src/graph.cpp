#include "../include/graph.h"

#include <fstream>
#include <iostream>

bool readGraph(const std::string& filename,
               AdjList& graph,
               int& vertices)
{
    std::ifstream fin(filename);

    if (!fin.is_open())
    {
        std::cout << "Error: Unable to open file " << filename << std::endl;
        return false;
    }

    fin >> vertices;

    graph.assign(vertices, std::vector<Edge>());

    int source;
    int destination;
    int weight;

    while (fin >> source >> destination >> weight)
    {
        Edge edge;

        edge.destination = destination;
        edge.weight = weight;

        graph[source].push_back(edge);
    }

    fin.close();

    return true;
}