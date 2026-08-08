#include "../include/bellman_ford.h"
#include "../include/floyd_warshall.h"
#include "../include/graph_io.h"
#include "../include/timer.h"
#include "../include/csr.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

static bool file_exists(const std::string& str_path)
{
    std::ifstream stream_fin(str_path);
    return stream_fin.good();
}

static void run_single_bf(const std::string& str_fileName)
{
    GraphInput struct_input;
    if (!read_directed_weighted_graph(str_fileName, struct_input))
    {
        std::cerr << "Error: Failed to read graph from " << str_fileName << "\n";
        return;
    }

    // Convert adjacency list to CSR representation (preprocessing, not timed).
    CSRGraph struct_csr = convert_to_csr(struct_input.v_adjList);

    std::vector<int> v_distances;

    // Time only the core algorithm execution (including negative cycle check pass).
    TimePoint t_start = start_timer();
    bool b_hasNegativeCycle = run_bellman_ford(struct_input.i_vertexCount, struct_csr, struct_input.i_source, v_distances);
    double d_elapsedUs = stop_timer(t_start);

    // If it took less than 1000 microseconds, run it 10000 times to get a stable average
    if (d_elapsedUs < 1000.0)
    {
        int i_targetRuns = 10000;
        t_start = start_timer();
        for (int i_r = 0; i_r < i_targetRuns; ++i_r)
        {
            run_bellman_ford(struct_input.i_vertexCount, struct_csr, struct_input.i_source, v_distances);
        }
        d_elapsedUs = stop_timer(t_start) / i_targetRuns;
    }

    std::cout << "Algorithm: Bellman-Ford\n";
    std::cout << "Source: " << struct_input.i_source << "\n";
    if (b_hasNegativeCycle)
    {
        std::cout << "Negative cycle: true\n";
    }
    else
    {
        std::cout << "Vertex Distance\n";
        for (int i_i = 0; i_i < struct_input.i_vertexCount; ++i_i)
        {
            if (v_distances[i_i] == i_BF_INF)
            {
                std::cout << i_i << " INF\n";
            }
            else
            {
                std::cout << i_i << " " << v_distances[i_i] << "\n";
            }
        }
        std::cout << "Negative cycle: none\n";
    }
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Execution time: " << d_elapsedUs << " us\n";
}

static void run_single_fw(const std::string& str_fileName)
{
    int i_vertexCount = 0;
    std::vector<std::vector<int>> v_matrix;

    if (!read_adjacency_matrix(str_fileName, i_vertexCount, v_matrix))
    {
        std::cerr << "Error: Failed to read adjacency matrix from " << str_fileName << "\n";
        return;
    }

    std::vector<std::vector<int>> v_matrixOrig = v_matrix;

    // Time only the core algorithm execution (including negative cycle check pass).
    TimePoint t_start = start_timer();
    bool b_hasNegativeCycle = run_floyd_warshall(i_vertexCount, v_matrix);
    double d_elapsedUs = stop_timer(t_start);

    // If it took less than 1000 microseconds, run it in a loop to get a stable average
    if (d_elapsedUs < 1000.0)
    {
        int i_targetRuns = 10000;
        if (i_vertexCount >= 100) i_targetRuns = 100;
        else if (i_vertexCount >= 50) i_targetRuns = 1000;

        t_start = start_timer();
        for (int i_r = 0; i_r < i_targetRuns; ++i_r)
        {
            std::vector<std::vector<int>> v_matrixCopy = v_matrixOrig;
            run_floyd_warshall(i_vertexCount, v_matrixCopy);
        }
        d_elapsedUs = stop_timer(t_start) / i_targetRuns;
    }

    std::cout << "Algorithm: Floyd-Warshall\n";
    if (b_hasNegativeCycle)
    {
        std::cout << "Negative cycle: true\n";
    }
    else
    {
        std::cout << "Distance matrix:\n";
        for (int i_r = 0; i_r < i_vertexCount; ++i_r)
        {
            for (int i_c = 0; i_c < i_vertexCount; ++i_c)
            {
                if (v_matrix[i_r][i_c] == i_INF_VAL)
                {
                    std::cout << "INF";
                }
                else
                {
                    std::cout << v_matrix[i_r][i_c];
                }
                if (i_c < i_vertexCount - 1)
                {
                    std::cout << " ";
                }
            }
            std::cout << "\n";
        }
        std::cout << "Negative cycle: none\n";
    }
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Execution time: " << d_elapsedUs << " us\n";
}

static void run_all_bf()
{
    std::vector<std::string> v_bfFiles = {
        "bf_10.txt",
        "bf_100.txt",
        "bf_10000.txt",
        "bf_50000.txt",
        "bf_100000.txt"
    };

    std::cout << "\n=== Running All Bellman-Ford Benchmarks ===\n";
    for (const std::string& str_file : v_bfFiles)
    {
        std::string str_path = "tests/" + str_file;
        if (!file_exists(str_path) && !file_exists(str_file))
        {
            std::cout << "File " << str_file << " not found, skipping...\n";
            continue;
        }
        std::cout << "\nRunning Bellman-Ford on " << str_file << ":\n";
        run_single_bf(str_file);
    }
}

static void run_all_fw()
{
    std::vector<std::string> v_fwFiles = {
        "fw_10.txt",
        "fw_100.txt",
        "fw_500.txt",
        "fw_1000.txt",
        "fw_2000.txt"
    };

    std::cout << "\n=== Running All Floyd-Warshall Benchmarks ===\n";
    for (const std::string& str_file : v_fwFiles)
    {
        std::string str_path = "tests/" + str_file;
        if (!file_exists(str_path) && !file_exists(str_file))
        {
            std::cout << "File " << str_file << " not found, skipping...\n";
            continue;
        }
        std::cout << "\nRunning Floyd-Warshall on " << str_file << ":\n";
        run_single_fw(str_file);
    }
}

int main(int argc, char* argv[])
{

    if (argc < 2)
    {
        int i_choice = -1;
        while (true)
        {
            std::cout << "\n===== Shortest Paths Algorithm Selector =====\n";
            std::cout << "1. Bellman-Ford (SSSP)\n";
            std::cout << "2. Floyd-Warshall (APSP)\n";
            std::cout << "0. Exit\n";
            std::cout << "Enter choice: ";
            if (!(std::cin >> i_choice))
            {
                break;
            }
            if (i_choice == 0)
            {
                break;
            }
            if (i_choice != 1 && i_choice != 2)
            {
                std::cout << "Invalid choice.\n";
                continue;
            }

            std::string str_testFile;
            std::cout << "Enter test file name (e.g. bf_10.txt, fw_10.txt): ";
            std::cin >> str_testFile;

            if (i_choice == 1)
            {
                run_single_bf(str_testFile);
            }
            else
            {
                run_single_fw(str_testFile);
            }
        }
        return 0;
    }

    std::string str_arg1 = argv[1];

    if (str_arg1 == "--all-tests")
    {
        if (argc < 3)
        {
            std::cerr << "Error: Specify algorithm (bellman-ford or floyd-warshall) for --all-tests.\n";
            return 1;
        }
        std::string str_algo = argv[2];
        if (str_algo == "bellman-ford")
        {
            run_all_bf();
        }
        else if (str_algo == "floyd-warshall")
        {
            run_all_fw();
        }
        else
        {
            std::cerr << "Error: Unknown algorithm '" << str_algo << "'\n";
            return 1;
        }
    }
    else if (str_arg1 == "bellman-ford")
    {
        if (argc < 3)
        {
            std::cerr << "Error: Missing test file path.\n";
            return 1;
        }
        run_single_bf(argv[2]);
    }
    else if (str_arg1 == "floyd-warshall")
    {
        if (argc < 3)
        {
            std::cerr << "Error: Missing test file path.\n";
            return 1;
        }
        run_single_fw(argv[2]);
    }
    else
    {
        std::cerr << "Error: Unknown argument '" << str_arg1 << "'\n";
        return 1;
    }

    return 0;
}
