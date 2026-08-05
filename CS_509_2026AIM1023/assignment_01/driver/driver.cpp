#include "../include/gemm.h"
#include "../include/matrix.h"
#include "../include/timer.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Default cache block size for the blocked matrix multiplication.
static const int i_DEFAULT_BLOCK_SIZE = 32;

// Display help menu detailing command parameters.
static void print_usage()
{
    std::cout << "Usage:\n";
    std::cout << "  gemm <simple|blocking|both> <test_file> [block_size]\n";
    std::cout << "  gemm --all-tests [simple|blocking|both] [block_size]\n";
    std::cout << "  gemm (interactive mode)\n";
}

// Check element-wise equivalence of two matrices.
static bool matrices_equal(const Matrix& mat_left, const Matrix& mat_right)
{
    if (mat_left.size() != mat_right.size())
    {
        return false;
    }

    for (size_t i_row = 0; i_row < mat_left.size(); i_row++)
    {
        if (mat_left[i_row].size() != mat_right[i_row].size())
        {
            return false;
        }

        for (size_t i_col = 0; i_col < mat_left[i_row].size(); i_col++)
        {
            if (mat_left[i_row][i_col] != mat_right[i_row][i_col])
            {
                return false;
            }
        }
    }

    return true;
}

// Executes simple GEMM and measures the runtime.
static double run_simple_gemm(const Matrix& mat_a, const Matrix& mat_b, Matrix& mat_c, int i_m, int i_k, int i_n)
{
    TimePoint t_start = start_timer();
    gemm_simple(mat_a, mat_b, mat_c, i_m, i_k, i_n);
    return stop_timer(t_start);
}

// Executes blocked GEMM and measures the runtime.
static double run_blocking_gemm(const Matrix& mat_a, const Matrix& mat_b, Matrix& mat_c,
                                int i_m, int i_k, int i_n, int i_block_size)
{
    TimePoint t_start = start_timer();
    gemm_blocking(mat_a, mat_b, mat_c, i_m, i_k, i_n, i_block_size);
    return stop_timer(t_start);
}

// Prints result matrices and measured runtimes.
static void print_gemm_result(const std::string& str_algorithm_name, const Matrix& mat_c, double d_elapsed_ms)
{
    std::cout << "Algorithm: " << str_algorithm_name << "\n";
    std::cout << "Result matrix:\n";
    print_matrix(mat_c);
    std::cout << "Execution time: " << d_elapsed_ms << " ms\n";
}

// Loads a test file, runs the specified mode (simple/blocking/both), and prints outcomes.
static int run_gemm_on_file(const std::string& str_test_file, const std::string& str_mode, int i_block_size)
{
    Matrix mat_a;
    Matrix mat_b;
    Matrix mat_c;
    int i_m = 0;
    int i_k = 0;
    int i_n = 0;

    // Load matrices from text file.
    if (!matrix_read(str_test_file, mat_a, mat_b, i_m, i_k, i_n))
    {
        return 1;
    }

    std::cout << "\nTest file: " << str_test_file << "\n";
    std::cout << "Dimensions: A(" << i_m << " x " << i_k << "), B(" << i_k << " x " << i_n << ")\n\n";

    if (str_mode == "simple" || str_mode == "both")
    {
        mat_c = create_matrix(i_m, i_n);
        double d_elapsed_ms = run_simple_gemm(mat_a, mat_b, mat_c, i_m, i_k, i_n);
        print_gemm_result("GEMM Simple", mat_c, d_elapsed_ms);
        std::cout << "\n";
    }

    if (str_mode == "blocking" || str_mode == "both")
    {
        mat_c = create_matrix(i_m, i_n);
        double d_elapsed_ms = run_blocking_gemm(mat_a, mat_b, mat_c, i_m, i_k, i_n, i_block_size);
        print_gemm_result("GEMM Blocking", mat_c, d_elapsed_ms);
        std::cout << "Block size: " << i_block_size << "\n\n";
    }

    // Verify matrix equality if both modes were run.
    if (str_mode == "both")
    {
        Matrix mat_simple_res = create_matrix(i_m, i_n);
        Matrix mat_blocking_res = create_matrix(i_m, i_n);

        gemm_simple(mat_a, mat_b, mat_simple_res, i_m, i_k, i_n);
        gemm_blocking(mat_a, mat_b, mat_blocking_res, i_m, i_k, i_n, i_block_size);

        bool b_equal = matrices_equal(mat_simple_res, mat_blocking_res);
        std::cout << "Result match: " << (b_equal ? "Pass" : "Fail") << "\n\n";
    }

    return 0;
}

// Checks if a file exists on disk.
static bool test_file_exists(const std::string& str_path)
{
    std::ifstream stream_fin(str_path);
    return stream_fin.good();
}

// Scans the tests folder for files matching the gemm_test_XX.txt format.
static std::vector<std::string> collect_test_files()
{
    std::vector<std::string> v_files;

    for (int i_idx = 1; i_idx <= 99; i_idx++)
    {
        std::ostringstream stream_name;
        stream_name << "tests/gemm_test_";
        if (i_idx < 10)
        {
            stream_name << "0";
        }
        stream_name << i_idx << ".txt";

        if (test_file_exists(stream_name.str()))
        {
            v_files.push_back(stream_name.str());
        }
    }

    return v_files;
}

// Runs execution on all tests found in the tests directory.
static int run_all_tests(const std::string& str_mode, int i_block_size)
{
    std::vector<std::string> v_test_files = collect_test_files();

    if (v_test_files.empty())
    {
        std::cerr << "Error: No test files found in tests/\n";
        return 1;
    }

    for (const std::string& str_test_file : v_test_files)
    {
        if (run_gemm_on_file(str_test_file, str_mode, i_block_size) != 0)
        {
            return 1;
        }
    }

    return 0;
}

// Interactive command line interface.
static int run_interactive()
{
    std::string str_test_file;
    int i_choice = 0;
    int i_block_size = i_DEFAULT_BLOCK_SIZE;

    std::cout << "Enter test file path (e.g. tests/gemm_test_01.txt): ";
    std::cin >> str_test_file;

    std::cout << "Select algorithm:\n";
    std::cout << "1. Simple GEMM\n";
    std::cout << "2. Blocking GEMM\n";
    std::cout << "3. Both\n";
    std::cout << "Enter choice: ";
    std::cin >> i_choice;

    if (i_choice == 2 || i_choice == 3)
    {
        std::cout << "Enter block size (default " << i_DEFAULT_BLOCK_SIZE << "): ";
        std::cin >> i_block_size;
        if (i_block_size <= 0)
        {
            i_block_size = i_DEFAULT_BLOCK_SIZE;
        }
    }

    std::string str_mode = "simple";
    if (i_choice == 2)
    {
        str_mode = "blocking";
    }
    else if (i_choice == 3)
    {
        str_mode = "both";
    }

    return run_gemm_on_file(str_test_file, str_mode, i_block_size);
}

int main(int argc, char* argv[])
{
    // If no arguments provided, enter interactive mode.
    if (argc == 1)
    {
        return run_interactive();
    }

    // Run batch tests flag.
    if (argc >= 2 && std::string(argv[1]) == "--all-tests")
    {
        std::string str_mode = "both";
        int i_block_size = i_DEFAULT_BLOCK_SIZE;

        if (argc >= 3)
        {
            str_mode = argv[2];
        }

        if (argc >= 4)
        {
            i_block_size = std::stoi(argv[3]);
        }

        if (str_mode != "simple" && str_mode != "blocking" && str_mode != "both")
        {
            print_usage();
            return 1;
        }

        return run_all_tests(str_mode, i_block_size);
    }

    // Direct mode execution on specified file.
    if (argc < 3)
    {
        print_usage();
        return 1;
    }

    std::string str_mode = argv[1];
    std::string str_test_file = argv[2];
    int i_block_size = i_DEFAULT_BLOCK_SIZE;

    if (argc >= 4)
    {
        i_block_size = std::stoi(argv[3]);
    }

    if (str_mode != "simple" && str_mode != "blocking" && str_mode != "both")
    {
        print_usage();
        return 1;
    }

    return run_gemm_on_file(str_test_file, str_mode, i_block_size);
}
