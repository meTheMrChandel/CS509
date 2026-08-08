#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Helper to run shell command and output command trace.
static int run_command(const std::string& str_command)
{
    std::cout << "\n> " << str_command << "\n";
    return std::system(str_command.c_str());
}

// Verifies file existence on local storage.
static bool file_exists(const std::string& str_path)
{
    std::ifstream stream_fin(str_path);
    return stream_fin.good();
}

// Generates a list of all GEMM test files found in tests folder.
static std::vector<std::string> list_test_files()
{
    std::vector<std::string> v_files;

    for (int i_idx = 1; i_idx <= 99; i_idx++)
    {
        std::ostringstream stream_name;
        stream_name << "../assignment_01/tests/gemm_test_";
        if (i_idx < 10)
        {
            stream_name << "0";
        }
        stream_name << i_idx << ".txt";

        if (file_exists(stream_name.str()))
        {
            std::ostringstream stream_display_name;
            stream_display_name << "gemm_test_";
            if (i_idx < 10)
            {
                stream_display_name << "0";
            }
            stream_display_name << i_idx << ".txt";
            v_files.push_back(stream_display_name.str());
        }
    }

    return v_files;
}

// Invokes Makefile compilation for Assignment 01.
static void compile_assignment_01()
{
    // Cwd of wrapper executable is under common_wrapper folder, so use relative path to assignment_01.
    if (run_command("mingw32-make -C ..\\assignment_01") != 0)
    {
        std::cout << "Error: Compilation failed for Assignment 01.\n";
    }
    else
    {
        std::cout << "Assignment 01 compiled successfully.\n";
    }
}

// Interactively prompts parameters to execute a single test case.
static void run_single_test()
{
    const std::string str_executable = "..\\assignment_01\\gemm.exe";

    if (!file_exists(str_executable))
    {
        std::cout << "Error: Executable not found. Compile Assignment 01 first.\n";
        return;
    }

    std::string str_mode;
    std::string str_test_file;
    int i_block_size = 32;

    std::cout << "Select mode (simple/blocking/both): ";
    std::cin >> str_mode;

    std::cout << "Enter test file name (e.g. gemm_test_01.txt): ";
    std::cin >> str_test_file;

    if (str_mode == "blocking" || str_mode == "both")
    {
        std::cout << "Enter block size (default 32): ";
        std::cin >> i_block_size;
    }

    std::string str_command = str_executable + " " + str_mode + " tests\\" + str_test_file;
    if (str_mode == "blocking" || str_mode == "both")
    {
        str_command += " " + std::to_string(i_block_size);
    }

    run_command(str_command);
}

// Configures and runs all test cases for matrix multiplication.
static void run_all_tests()
{
    const std::string str_executable = "..\\assignment_01\\gemm.exe";

    if (!file_exists(str_executable))
    {
        std::cout << "Error: Executable not found. Compile Assignment 01 first.\n";
        return;
    }

    std::string str_mode;
    int i_block_size = 32;

    std::cout << "Select mode (simple/blocking/both): ";
    std::cin >> str_mode;

    if (str_mode == "blocking" || str_mode == "both")
    {
        std::cout << "Enter block size (default 32): ";
        std::cin >> i_block_size;
    }

    std::string str_command = str_executable + " --all-tests " + str_mode + " " + std::to_string(i_block_size);
    run_command(str_command);
}

// Submenu interface for Assignment 01.
static void show_assignment_01_menu()
{
    int i_choice = -1;

    while (i_choice != 0)
    {
        std::cout << "\n===== Assignment 01: GEMM =====\n";
        std::cout << "1. Compile Assignment 01\n";
        std::cout << "2. Run one test file\n";
        std::cout << "3. Run all test files\n";
        std::cout << "4. List available test files\n";
        std::cout << "0. Back\n";
        std::cout << "Enter choice: ";
        std::cin >> i_choice;

        switch (i_choice)
        {
            case 1:
                compile_assignment_01();
                break;
            case 2:
                run_single_test();
                break;
            case 3:
                run_all_tests();
                break;
            case 4:
            {
                std::vector<std::string> v_files = list_test_files();
                if (v_files.empty())
                {
                    std::cout << "No test files found.\n";
                }
                else
                {
                    std::cout << "Available test files:\n";
                    for (const std::string& str_file : v_files)
                    {
                        std::cout << "  - " << str_file << "\n";
                    }
                }
                break;
            }
            default:
                if (i_choice != 0)
                {
                    std::cout << "Invalid choice.\n";
                }
                break;
        }
    }
}

// Invokes Makefile compilation for Assignment 02.
static void compile_assignment_02()
{
    // Cwd of wrapper executable is under common_wrapper folder, so use relative path to assignment_02.
    if (run_command("mingw32-make -C ..\\assignment_02") != 0)
    {
        std::cout << "Error: Compilation failed for Assignment 02.\n";
    }
    else
    {
        std::cout << "Assignment 02 compiled successfully.\n";
    }
}

// Runs single selected test case for Assignment 02.
static void run_single_test_02()
{
    const std::string str_executable = "..\\assignment_02\\shortest_path.exe";

    if (!file_exists(str_executable))
    {
        std::cout << "Error: Executable not found. Compile Assignment 02 first.\n";
        return;
    }

    std::string str_algo;
    std::string str_testFile;

    std::cout << "Select algorithm (bellman-ford/floyd-warshall): ";
    std::cin >> str_algo;

    std::cout << "Enter test file name (e.g. bf_10.txt, fw_10.txt): ";
    std::cin >> str_testFile;

    std::string str_command = str_executable + " " + str_algo + " tests\\" + str_testFile;
    run_command(str_command);
}

// Runs all test cases for Assignment 02.
static void run_all_tests_02()
{
    const std::string str_executable = "..\\assignment_02\\shortest_path.exe";

    if (!file_exists(str_executable))
    {
        std::cout << "Error: Executable not found. Compile Assignment 02 first.\n";
        return;
    }

    std::string str_algo;
    std::cout << "Select algorithm (bellman-ford/floyd-warshall): ";
    std::cin >> str_algo;

    std::string str_command = str_executable + " --all-tests " + str_algo;
    run_command(str_command);
}

// Submenu interface for Assignment 02.
static void show_assignment_02_menu()
{
    int i_choice = -1;

    while (i_choice != 0)
    {
        std::cout << "\n===== Assignment 02: Shortest Paths =====\n";
        std::cout << "1. Compile Assignment 02\n";
        std::cout << "2. Run one test file\n";
        std::cout << "3. Run all test files (benchmarks)\n";
        std::cout << "0. Back\n";
        std::cout << "Enter choice: ";
        std::cin >> i_choice;

        switch (i_choice)
        {
            case 1:
                compile_assignment_02();
                break;
            case 2:
                run_single_test_02();
                break;
            case 3:
                run_all_tests_02();
                break;
            default:
                if (i_choice != 0)
                {
                    std::cout << "Invalid choice.\n";
                }
                break;
        }
    }
}

int main()
{
    int i_choice = -1;

    while (i_choice != 0)
    {
        std::cout << "\n=====================================\n";
        std::cout << "   CS509 Individual Repository Menu\n";
        std::cout << "=====================================\n";
        std::cout << "1. Assignment 01 - GEMM\n";
        std::cout << "2. Assignment 02 - Shortest Paths\n";
        std::cout << "3. Assignment 03 (not available)\n";
        std::cout << "4. Assignment 04 (not available)\n";
        std::cout << "5. Assignment 05 (not available)\n";
        std::cout << "6. Assignment 06 (not available)\n";
        std::cout << "7. Assignment 07 (not available)\n";
        std::cout << "8. Assignment 08 (not available)\n";
        std::cout << "9. Assignment 09 (not available)\n";
        std::cout << "10. Assignment 10 (not available)\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> i_choice;

        switch (i_choice)
        {
            case 1:
                show_assignment_01_menu();
                break;
            case 2:
                show_assignment_02_menu();
                break;
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                std::cout << "Assignment " << i_choice << " is not available yet.\n";
                break;
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }

    return 0;
}
