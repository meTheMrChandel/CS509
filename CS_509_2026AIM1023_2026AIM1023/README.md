# CS509 Laboratory Repository

## Repository Overview

This repository contains buddy (pair) assignments for CS509 - Parallel Computer Architecture. Assignment 01 implements BFS, DFS, and SSSP (Dijkstra) on graphs stored in CSR format.

## Student / Pair Details

- **Student 1:** Vishal Chandel (2026AIM1023)
- **Student 2:** (Buddy partner entry number)
- **Program:** M.Tech Artificial Intelligence, IIT Ropar

## Language and Environment

- **Language:** C++17
- **Compiler:** MinGW g++ (GCC)
- **Build Tool:** mingw32-make
- **Timing Method:** `std::chrono::high_resolution_clock`, reported in milliseconds (ms)
- **Platform:** Windows 10/11

## Directory Structure

```
CS_509_2026AIM1023_2026AIM1023/
|-- README.md
|-- common_wrapper/
|   |-- wrapper.cpp
|   `-- Makefile
|-- assignment_01/
    |-- driver/
    |-- include/
    |-- src/
    |-- tests/
    |-- Makefile
    `-- readme.md
```

## Common Wrapper: Build and Usage

```bash
cd common_wrapper
mingw32-make
wrapper.exe
```

The wrapper provides:

- Assignment selection menu
- Compile Assignment 01
- Run one selected test file
- Run all tests for one algorithm
- Run all algorithms on all test files

## General Conventions

- Graph input uses adjacency-list format with `SOURCE s` line
- Adjacency-list-to-CSR conversion is done before timing
- Timing includes only algorithm execution
- Vertex numbering uses 0 to V-1

---

## Assignment 01 - BFS, DFS, and SSSP

### Assignment Mode

Double / Buddy

### Objective

Implement graph traversal and shortest-path algorithms using CSR representation.

### Algorithm / Approach

- **CSR Conversion:** Adjacency list is converted to `row_ptr`, `col_idx`, and `values`.
- **BFS:** Queue-based level-order traversal with edge-count distances.
- **DFS:** Recursive depth-first traversal.
- **SSSP:** Dijkstra's algorithm with min-priority queue (positive weights only).

### Input Format

Unweighted (BFS/DFS):

```
V E
u degree neighbor1 neighbor2 ...
...
SOURCE s
```

Weighted (SSSP):

```
V E
u degree neighbor1 weight1 neighbor2 weight2 ...
...
SOURCE s
```

### Helper Functions / CSR Conversion

- `readUnweightedGraph()` / `readWeightedGraph()` in `src/graph.cpp`
- `convertToCSR()` in `src/csr.cpp`
- CSR conversion is excluded from reported runtime

### File Structure

| File | Purpose |
|------|---------|
| `driver/driver.cpp` | Input parsing, CSR setup, algorithm dispatch, output |
| `src/graph.cpp` | Adjacency-list file reader |
| `src/csr.cpp` | CSR conversion |
| `src/bfs.cpp`, `src/dfs.cpp`, `src/sssp.cpp` | Core algorithms |
| `tests/generate_graph_tests.py` | Generator for large graph test files |

### Compilation

```bash
cd assignment_01
mingw32-make
```

### Execution

```bash
graph_simulator.exe bfs tests/bfs_10.txt
graph_simulator.exe dfs tests/dfs_10.txt
graph_simulator.exe sssp tests/sssp_10.txt
graph_simulator.exe --all-tests bfs
graph_simulator.exe --all
```

Generate additional required scales:

```bash
cd tests
python generate_graph_tests.py --scales 100 10000 50000 100000
```

### Test Cases and Result Table

| Algorithm | Test File | Vertices | Edges | Input Type | Source | Expected Output | Actual Output | Time | Status |
|-----------|-----------|----------|-------|------------|--------|-----------------|---------------|------|--------|
| BFS | bfs_10.txt | 10 | 14 | Unweighted adjacency list (CSR) | 0 | Traversal + distances | (run locally) | (run locally) ms | Pass |
| DFS | dfs_10.txt | 10 | 14 | Unweighted adjacency list (CSR) | 0 | Valid DFS traversal | (run locally) | (run locally) ms | Pass |
| SSSP | sssp_10.txt | 10 | 16 | Positive weighted adjacency list (CSR) | 0 | Shortest distances | (run locally) | (run locally) ms | Pass |
| BFS | bfs_100.txt | 100 | 200 | Generated | 0 | - | (run locally) | (run locally) ms | - |
| BFS | bfs_10000.txt | 10000 | 20000 | Generated | 0 | - | (run locally) | (run locally) ms | - |
| BFS | bfs_50000.txt | 50000 | 100000 | Generated | 0 | - | (run locally) | (run locally) ms | - |
| BFS | bfs_100000.txt | 100000 | 200000 | Generated | 0 | - | (run locally) | (run locally) ms | - |

> Fill actual timing values after running on your machine.

### Complexity

- **CSR Conversion:** O(V + E)
- **BFS / DFS:** O(V + E)
- **Dijkstra (SSSP):** O((V + E) log V) with binary heap

### References

- CS509 Assignment 1 specification
- CS509 Lab Work Guidelines
