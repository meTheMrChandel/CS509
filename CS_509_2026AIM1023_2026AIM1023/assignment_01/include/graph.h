#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

struct Edge
{
    int destination;
    int weight;
};

using AdjList = std::vector<std::vector<Edge>>;

// For BFS and DFS
bool readUnweightedGraph(const std::string& filename,
                         AdjList& graph,
                         int& vertices);

// For Dijkstra
bool readWeightedGraph(const std::string& filename,
                       AdjList& graph,
                       int& vertices);

#endif