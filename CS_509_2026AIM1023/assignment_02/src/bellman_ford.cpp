#include "../include/bellman_ford.h"

// Runs the Bellman-Ford SSSP algorithm on a CSRGraph.
bool run_bellman_ford(int i_vertexCount, const CSRGraph& struct_csr, int i_source, std::vector<int>& v_distances)
{
    v_distances.assign(i_vertexCount, i_BF_INF);
    v_distances[i_source] = 0;

    // Relax all edges V-1 times.
    for (int i_pass = 1; i_pass <= i_vertexCount - 1; ++i_pass)
    {
        bool b_anyRelaxed = false;

        // Iterate over all vertices and their outgoing edges.
        for (int i_u = 0; i_u < i_vertexCount; ++i_u)
        {
            if (v_distances[i_u] == i_BF_INF)
            {
                continue;
            }

            int i_startEdge = struct_csr.v_rowPtr[i_u];
            int i_endEdge = struct_csr.v_rowPtr[i_u + 1];

            for (int i_e = i_startEdge; i_e < i_endEdge; ++i_e)
            {
                int i_v = struct_csr.v_colIndex[i_e];
                int i_w = struct_csr.v_edgeWeights[i_e];

                if (v_distances[i_u] + i_w < v_distances[i_v])
                {
                    v_distances[i_v] = v_distances[i_u] + i_w;
                    b_anyRelaxed = true;
                }
            }
        }

        // Optimization: If no edge was relaxed during a pass, we can terminate early.
        if (!b_anyRelaxed)
        {
            break;
        }
    }

    // Check for negative-weight cycles on the V-th pass.
    bool b_hasNegativeCycle = false;
    for (int i_u = 0; i_u < i_vertexCount; ++i_u)
    {
        if (v_distances[i_u] == i_BF_INF)
        {
            continue;
        }

        int i_startEdge = struct_csr.v_rowPtr[i_u];
        int i_endEdge = struct_csr.v_rowPtr[i_u + 1];

        for (int i_e = i_startEdge; i_e < i_endEdge; ++i_e)
        {
            int i_v = struct_csr.v_colIndex[i_e];
            int i_w = struct_csr.v_edgeWeights[i_e];

            if (v_distances[i_u] + i_w < v_distances[i_v])
            {
                b_hasNegativeCycle = true;
                break;
            }
        }
        if (b_hasNegativeCycle)
        {
            break;
        }
    }

    return b_hasNegativeCycle;
}
