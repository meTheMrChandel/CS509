#include "../include/graph.h"
#include "../include/csr.h"
#include "../include/bfs.h"
#include "../include/dfs.h"
#include "../include/sssp.h"
#include "../include/timer.h"

#include <iostream>

int main()
{
    AdjList graph;
    CSRGraph csrGraph;

    int vertices;

    std::string filename;

    std::cout << "=============================\n";
    std::cout << "      Graph Simulator\n";
    std::cout << "=============================\n";

    std::cout << "Select Algorithm\n";
    std::cout << "1. BFS\n";
    std::cout << "2. DFS\n";
    std::cout << "3. Dijkstra (SSSP)\n";
    std::cout << "Enter Choice: ";

    int choice;
    std::cin >> choice;

    std::cout << "Enter Input File: ";
    std::cin >> filename;

    bool status = false;

    if (choice == 1 || choice == 2)
    {
        status = readUnweightedGraph(filename, graph, vertices);
    }
    else if (choice == 3)
    {
        status = readWeightedGraph(filename, graph, vertices);
    }
    else
    {
        std::cout << "Invalid Choice\n";
        return 1;
    }

    if (!status)
        return 1;

    // Convert to CSR (NOT TIMED)
    csrGraph = convertToCSR(graph);

    int source;

    std::cout << "Enter Source Vertex: ";
    std::cin >> source;

    TimePoint start = startTimer();

    switch (choice)
    {
        case 1:
            bfs(csrGraph, source);
            break;

        case 2:
            dfs(csrGraph, source);
            break;

        case 3:
            dijkstra(csrGraph, source);
            break;
    }

    double elapsedTime = stopTimer(start);

    std::cout << "\nExecution Time : "
              << elapsedTime
              << " ms\n";

    return 0;
}