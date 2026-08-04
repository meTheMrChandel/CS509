#ifndef CSR_H
#define CSR_H

#include "graph.h"
#include <vector>

struct CSRGraph
{
    std::vector<int> rowPtr;
    std::vector<int> colIndex;
    std::vector<int> weights;
};

CSRGraph convertToCSR(const AdjList& graph);

#endif