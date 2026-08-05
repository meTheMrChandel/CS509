#include "../include/dfs.h"

// Recursive helper method to perform Depth-First Search exploration.
static void dfs_helper(const CSRGraph& struct_graph, int i_current, std::vector<bool>& v_visited,
                       std::vector<int>& v_traversal)
{
    v_visited[i_current] = true;
    v_traversal.push_back(i_current);

    int i_edge_start = struct_graph.v_row_ptr[i_current];
    int i_edge_end = struct_graph.v_row_ptr[i_current + 1];

    // Traverse all adjacent edge connections.
    for (int i_idx = i_edge_start; i_idx < i_edge_end; ++i_idx)
    {
        int i_neighbour = struct_graph.v_col_index[i_idx];

        // Recurse on unvisited paths.
        if (!v_visited[i_neighbour])
        {
            dfs_helper(struct_graph, i_neighbour, v_visited, v_traversal);
        }
    }
}

// Depth-First Search (DFS) traversal implementation on a CSR representation.
DFSResult dfs(const CSRGraph& struct_graph, int i_source)
{
    int i_vertex_count = static_cast<int>(struct_graph.v_row_ptr.size()) - 1;

    DFSResult struct_result;
    struct_result.v_traversal.reserve(i_vertex_count);

    std::vector<bool> v_visited(i_vertex_count, false);
    dfs_helper(struct_graph, i_source, v_visited, struct_result.v_traversal);

    return struct_result;
}
