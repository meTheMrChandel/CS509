# CS509 Laboratory Repository

## Repository Overview

This repository contains individual assignments for CS509 - Parallel Computer Architecture. Assignment 01 implements General Matrix Multiplication (GEMM) using both simple and blocking algorithms.

## Student Details

- **Name:** Vishal Chandel
- **Entry Number:** 2026AIM1023
- **Program:** M.Tech Artificial Intelligence, IIT Ropar

## Language and Environment

- **Language:** C++17
- **Compiler:** MinGW g++ (GCC)
- **Build Tool:** mingw32-make
- **Timing Method:** `std::chrono::high_resolution_clock`, reported in milliseconds (ms)
- **Platform:** Windows 10/11

## Directory Structure

```
CS_509_2026AIM1023/
|-- README.md
|-- common_wrapper/
|   |-- wrapper.cpp
|   `-- Makefile
|-- assignment_01/
    |-- driver/
    |   `-- driver.cpp
    |-- include/
    |   |-- gemm.h
    |   |-- matrix.h
    |   `-- timer.h
    |-- src/
    |   |-- gemm_blocking.cpp
    |   |-- gemm_simple.cpp
    |   |-- matrix.cpp
    |   `-- timer.cpp
    |-- tests/
    |   |-- gemm_test_01.txt
    |   |-- gemm_test_02.txt
    |   |-- gemm_test_03.txt
    |   |-- gemm_test_04.txt
    |   |-- gemm_test_05.txt
    |   `-- gemm_test_06.txt
    `-- Makefile
```

## Common Wrapper: Build and Usage

The wrapper acts as a main gateway program to compile and run assignments.

```powershell
cd common_wrapper
mingw32-make
.\wrapper.exe
```

The wrapper provides:
- Assignment selection menu
- Compile Assignment 01
- Run one selected test file
- Run all test files
- Clear error messages for missing executables or test files

## General Conventions

- One test case per `.txt` file in `assignment_01/tests/`
- Timing includes only core algorithm execution (excluding file I/O or output printing)
- Variables use type-prefixed snake_case naming style.

---

## Assignment 01 - GEMM

### Assignment Mode

Single (Individual)

### Objective

Implement and compare simple and blocking GEMM algorithms on the same matrix inputs.

### Algorithm / Approach

- **Simple GEMM:** Baseline nested triple loop matrix multiplication. It iterates row-by-row (i, j, k) to compute dot products.
- **Blocking GEMM:** Tiled multiplication. Divides matrices into submatrix blocks of size `block_size` to optimize cache hit rates by reuse.

### Input Format

```
M K N
A row 0 values
...
A row M-1 values
B row 0 values
...
B row K-1 values
```

### File Structure

| File | Purpose |
|------|---------|
| `driver/driver.cpp` | Command-line dispatch, reads matrix inputs, calls timers, outputs correctness / matches. |
| `src/gemm_simple.cpp` | Standard triple loop matrix multiplication. |
| `src/gemm_blocking.cpp` | Blocked matrix multiplication. |
| `src/matrix.cpp` | Matrix parsing, creation, and printing helpers. |
| `src/timer.cpp` | High-resolution clock utilities. |

### Compilation

```powershell
cd assignment_01
mingw32-make
```

### Execution

```powershell
# Run a single algorithm on a test file
.\gemm.exe simple tests/gemm_test_02.txt
.\gemm.exe blocking tests/gemm_test_02.txt 32
.\gemm.exe both tests/gemm_test_02.txt 32

# Run all tests in the tests folder
.\gemm.exe --all-tests both 32
```

### Test Cases and Result Table

| Test File | Input Type / Size | Expected Output | Actual Output | Simple Time (ms) | Blocking Time (ms) | Block Size | Status |
|-----------|-------------------|-----------------|---------------|-------------|---------------|------------|--------|
| gemm_test_01.txt | A(20x10), B(10x30) | Computed 20x30 matrix | Same as simple | 0.000 ms | 0.000 ms | 32 | Pass |
| gemm_test_02.txt | A(2x3), B(3x2) | [[58,64],[139,154]] | Same as simple | 0.000 ms | 0.000 ms | 32 | Pass |
| gemm_test_03.txt | A(50x50), B(50x50) | Computed 50x50 matrix | Same as simple | 1.336 ms | 1.336 ms | 32 | Pass |
| gemm_test_04.txt | A(100x100), B(100x100) | Computed 100x100 matrix | Same as simple | 8.968 ms | 8.968 ms | 32 | Pass |
| gemm_test_05.txt | A(250x250), B(250x250) | Computed 250x250 matrix | Same as simple | 150.12 ms | 152.82 ms | 32 | Pass |
| gemm_test_06.txt | A(500x500), B(500x500) | Computed 500x500 matrix | Same as simple | 1255.03 ms | 1269.85 ms | 32 | Pass |

### Complexity

- **Simple GEMM:** Time complexity $O(MKN)$, Space complexity $O(MK + KN + MN)$
- **Blocking GEMM:** Time complexity $O(MKN)$, Space complexity $O(MK + KN + MN)$

### References

- CS509 Assignment 1 Specification
- CS509 Lab Work Guidelines
