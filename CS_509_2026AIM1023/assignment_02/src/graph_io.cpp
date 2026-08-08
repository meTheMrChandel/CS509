#include "../include/graph_io.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Helper to open graph file, checks local directory first, then tests/ folder.
static std::ifstream open_graph_file(const std::string& str_fileName)
{
    std::ifstream stream_fin(str_fileName);
    if (!stream_fin.is_open())
    {
        std::string str_altPath = "tests/" + str_fileName;
        stream_fin.open(str_altPath);
    }
    return stream_fin;
}

// Reads a directed weighted graph for Bellman-Ford.
bool read_directed_weighted_graph(const std::string& str_fileName, GraphInput& struct_input)
{
    std::ifstream stream_fin = open_graph_file(str_fileName);
    if (!stream_fin.is_open())
    {
        std::cerr << "Error: Unable to open file " << str_fileName << "\n";
        return false;
    }

    if (!(stream_fin >> struct_input.i_vertexCount >> struct_input.i_edgeCount))
    {
        std::cerr << "Error: Failed to read vertex and edge counts.\n";
        return false;
    }

    if (struct_input.i_vertexCount <= 0)
    {
        std::cerr << "Error: Invalid number of vertices.\n";
        return false;
    }

    struct_input.v_adjList.assign(struct_input.i_vertexCount, std::vector<Edge>());

    // We expect struct_input.i_vertexCount lines of adjacency list, one for each vertex 0 to V-1.
    for (int i_i = 0; i_i < struct_input.i_vertexCount; ++i_i)
    {
        int i_vertexId = -1;
        int i_degree = -1;
        if (!(stream_fin >> i_vertexId >> i_degree))
        {
            std::cerr << "Error: Failed to read vertex ID and degree at row index " << i_i << ".\n";
            return false;
        }

        if (i_vertexId < 0 || i_vertexId >= struct_input.i_vertexCount)
        {
            std::cerr << "Error: Vertex ID " << i_vertexId << " is out of range.\n";
            return false;
        }

        for (int i_d = 0; i_d < i_degree; ++i_d)
        {
            int i_neighbor = -1;
            int i_weight = 0;
            if (!(stream_fin >> i_neighbor >> i_weight))
            {
                std::cerr << "Error: Failed to read neighbor and weight for vertex " << i_vertexId << ".\n";
                return false;
            }

            if (i_neighbor < 0 || i_neighbor >= struct_input.i_vertexCount)
            {
                std::cerr << "Error: Neighbor ID " << i_neighbor << " is out of range.\n";
                return false;
            }

            Edge struct_edge;
            struct_edge.i_destination = i_neighbor;
            struct_edge.i_weight = i_weight;
            struct_input.v_adjList[i_vertexId].push_back(struct_edge);
        }
    }

    // Now look for SOURCE s keyword line
    std::string str_token;
    bool b_foundSource = false;
    while (stream_fin >> str_token)
    {
        if (str_token == "SOURCE")
        {
            if (stream_fin >> struct_input.i_source)
            {
                b_foundSource = true;
                break;
            }
            else
            {
                std::cerr << "Error: Missing source vertex ID after SOURCE keyword.\n";
                return false;
            }
        }
    }

    if (!b_foundSource)
    {
        std::cerr << "Error: SOURCE keyword line not found in graph file.\n";
        return false;
    }

    if (struct_input.i_source < 0 || struct_input.i_source >= struct_input.i_vertexCount)
    {
        std::cerr << "Error: Source vertex " << struct_input.i_source << " is out of range.\n";
        return false;
    }

    stream_fin.close();
    return true;
}

// Reads a dense matrix for Floyd-Warshall from file.
bool read_adjacency_matrix(const std::string& str_fileName, int& i_vertexCount, std::vector<std::vector<int>>& v_matrix)
{
    std::ifstream stream_fin = open_graph_file(str_fileName);
    if (!stream_fin.is_open())
    {
        std::cerr << "Error: Unable to open file " << str_fileName << "\n";
        return false;
    }

    if (!(stream_fin >> i_vertexCount))
    {
        std::cerr << "Error: Failed to read vertex count.\n";
        return false;
    }

    if (i_vertexCount <= 0)
    {
        std::cerr << "Error: Invalid number of vertices.\n";
        return false;
    }

    v_matrix.assign(i_vertexCount, std::vector<int>(i_vertexCount, i_INF_VAL));

    for (int i_r = 0; i_r < i_vertexCount; ++i_r)
    {
        for (int i_c = 0; i_c < i_vertexCount; ++i_c)
        {
            std::string str_val;
            if (!(stream_fin >> str_val))
            {
                std::cerr << "Error: Failed to read matrix value at row " << i_r << ", col " << i_c << ".\n";
                return false;
            }

            if (str_val == "INF")
            {
                v_matrix[i_r][i_c] = i_INF_VAL;
            }
            else
            {
                try
                {
                    v_matrix[i_r][i_c] = std::stoi(str_val);
                }
                catch (...)
                {
                    std::cerr << "Error: Invalid matrix value '" << str_val << "' at row " << i_r << ", col " << i_c << ".\n";
                    return false;
                }
            }

            // Entry (i, i) must be 0
            if (i_r == i_c && v_matrix[i_r][i_c] != 0)
            {
                std::cerr << "Warning: Entry (" << i_r << ", " << i_c << ") on diagonal is " << v_matrix[i_r][i_c] << " but is expected to be 0.\n";
            }
        }
    }

    stream_fin.close();
    return true;
}
