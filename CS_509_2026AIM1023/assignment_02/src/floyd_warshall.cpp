#include "../include/floyd_warshall.h"

// Runs the Floyd-Warshall all-pairs shortest path algorithm.
bool run_floyd_warshall(int i_vertexCount, std::vector<std::vector<int>>& v_matrix)
{
    // Floyd-Warshall DP updates: dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
    for (int i_k = 0; i_k < i_vertexCount; ++i_k)
    {
        for (int i_i = 0; i_i < i_vertexCount; ++i_i)
        {
            for (int i_j = 0; i_j < i_vertexCount; ++i_j)
            {
                if (v_matrix[i_i][i_k] != i_INF_VAL && v_matrix[i_k][i_j] != i_INF_VAL)
                {
                    if (v_matrix[i_i][i_k] + v_matrix[i_k][i_j] < v_matrix[i_i][i_j])
                    {
                        v_matrix[i_i][i_j] = v_matrix[i_i][i_k] + v_matrix[i_k][i_j];
                    }
                }
            }
        }
    }

    // Check for negative-weight cycle: any negative value on diagonal.
    bool b_hasNegativeCycle = false;
    for (int i_i = 0; i_i < i_vertexCount; ++i_i)
    {
        if (v_matrix[i_i][i_i] < 0)
        {
            b_hasNegativeCycle = true;
            break;
        }
    }

    return b_hasNegativeCycle;
}
