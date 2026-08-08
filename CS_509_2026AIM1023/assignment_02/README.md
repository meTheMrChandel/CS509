# CS509 - Assignment 2 (Individual Task)

## Student Details

- **Name:** Vishal Chandel
- **Entry Number:** 2026AIM1023
- **Program:** M.Tech Artificial Intelligence, IIT Ropar

---

## Objective

This project implements the individual tasks for **CS509 Assignment 2**:
1. **Bellman-Ford Algorithm:** Computes the single-source shortest path (SSSP) on a directed graph with possible negative edge weights using Compressed Sparse Row (CSR) representation.
2. **Floyd-Warshall Algorithm:** Computes all-pairs shortest paths (APSP) using a dense adjacency matrix representation.

Both algorithms include detection of negative-weight cycles. 

---

## Language and Environment

- **Language:** C++17
- **Compiler:** MinGW g++ (GCC)
- **Build Tool:** mingw32-make
- **Timing Method:** `std::chrono::high_resolution_clock` (reported in milliseconds `ms`)
- **Platform:** Windows 10/11

---

## Directory Structure

```
CS_509_2026AIM1023/
|-- common_wrapper/
|   |-- wrapper.cpp
|   |-- wrapper.exe
|   `-- Makefile
|-- assignment_02/
|   |-- driver/
|   |   `-- driver.cpp
|   |-- include/
|   |   |-- csr.h
|   |   |-- timer.h
|   |   |-- graph_io.h
|   |   |-- bellman_ford.h
|   |   `-- floyd_warshall.h
|   |-- src/
|   |   |-- csr.cpp
|   |   |-- timer.cpp
|   |   |-- graph_io.cpp
|   |   |-- bellman_ford.cpp
|   |   `-- floyd_warshall.cpp
|   |-- tests/
|   |   |-- bf_5.txt
|   |   |-- bf_10.txt
|   |   |-- bf_100.txt
|   |   |-- bf_neg_cycle.txt
|   |   |-- fw_5.txt
|   |   |-- fw_10.txt
|   |   |-- fw_100.txt
|   |   `-- fw_neg_cycle.txt
|   |-- Makefile
|   |-- README.md
|   `-- Assignment 2 Software Lab.pdf
```

---

## Compilation and Execution

### Compilation

To compile Assignment 2, navigate to the `assignment_02` directory and run:
```powershell
cd assignment_02
mingw32-make
```
This builds the program `shortest_paths.exe`.

### Execution

#### Running Bellman-Ford SSSP
```powershell
.\shortest_paths.exe bellman-ford tests\bf_10.txt
```

#### Running Floyd-Warshall APSP
```powershell
.\shortest_paths.exe floyd-warshall tests\fw_10.txt
```

#### Running All Tests Benchmarks
```powershell
.\shortest_paths.exe --all-tests bellman-ford
.\shortest_paths.exe --all-tests floyd-warshall
```

---

## Naming Conventions

All variables in this project adhere to the specified naming convention:
- **Type Prefix (snake_case):** e.g., `i_` (int), `d_` (double), `b_` (bool), `str_` (string), `v_` (vector), `struct_` (structure).
- **Variable Name (camelCase):** e.g., `i_vertexCount`, `str_fileName`, `b_hasNegativeCycle`, `v_rowPtr`.

---

## Graph Test Cases and Properties

All test cases are manually generated and stored under `assignment_02/tests/`:

1. **`bf_5.txt` / `fw_5.txt`:** Directed graph with 5 vertices and 10 edges. Contains negative edge weights but no negative cycle. Used to verify the example from the PDF.
2. **`bf_10.txt` / `fw_10.txt`:** Directed graph with 10 vertices and 15 edges. Contains negative weight edges (e.g., $3 \rightarrow 6$ weight $-2$, $6 \rightarrow 7$ weight $-3$) but no negative cycle.
3. **`bf_100.txt` / `fw_100.txt`:** Directed Acyclic Graph (DAG) with 100 vertices and 516 edges. Contains negative weights. Since it is a DAG, it has no cycles, ensuring no negative cycles.
4. **`bf_neg_cycle.txt` / `fw_neg_cycle.txt`:** 3-vertex graph containing a negative weight cycle ($0 \rightarrow 1 \rightarrow 2 \rightarrow 0$ with total cycle weight $1 - 5 + 1 = -3$).

---

## Bellman-Ford and Floyd-Warshall Cross-Check Verification

For graph sizes $V=10$ and $V=100$, Bellman-Ford was run from every vertex as the source node, and the resulting shortest distances were matched row-by-row with the Floyd-Warshall output matrix.

### V = 10 Verification Output
For every source vertex $s \in [0, 9]$, the distances computed by Bellman-Ford match the corresponding row $s$ of the Floyd-Warshall distance matrix:

- **Source 0:** `0 5 3 7 9 4 5 2 7 3` (FW Row 0: `0 5 3 7 9 4 5 2 7 3`)
- **Source 1:** `INF 0 INF 2 4 5 0 -3 8 -2` (FW Row 1: `INF 0 INF 2 4 5 0 -3 8 -2`)
- **Source 2:** `INF INF 0 INF INF 1 INF INF 4 6` (FW Row 2: `INF INF 0 INF INF 1 INF INF 4 6`)
- **Source 3:** `INF INF INF 0 INF 3 -2 -5 6 -4` (FW Row 3: `INF INF INF 0 INF 3 -2 -5 6 -4`)
- **Source 4:** `INF INF INF INF 0 INF 2 -1 INF 0` (FW Row 4: `INF INF INF INF 0 INF 2 -1 INF 0`)
- **Source 5:** `INF INF INF INF INF 0 INF INF 3 5` (FW Row 5: `INF INF INF INF INF 0 INF INF 3 5`)
- **Source 6:** `INF INF INF INF INF INF 0 -3 INF -2` (FW Row 6: `INF INF INF INF INF INF 0 -3 INF -2`)
- **Source 7:** `INF INF INF INF INF INF INF 0 INF 1` (FW Row 7: `INF INF INF INF INF INF INF 0 INF 1`)
- **Source 8:** `INF INF INF INF INF INF INF INF 0 2` (FW Row 8: `INF INF INF INF INF INF INF INF 0 2`)
- **Source 9:** `INF INF INF INF INF INF INF INF INF 0` (FW Row 9: `INF INF INF INF INF INF INF INF INF 0`)

The cross-check succeeded with **100% agreement** for both $V=10$ and $V=100$ graph structures.

---

## Result Table (Assignment 2 Benchmarks)

The following table records the execution timings for each test case. All timing runs exclude I/O preprocessing and matrix/CSR conversion overhead. For very fast inputs, the timing is averaged over 10,000 runs to obtain an accurate sub-microsecond result.

| Algorithm | Test File | Vertices | Edges | Source | Negative Cycle | Expected Output | Actual Output | Time (us) | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Bellman-Ford** | `bf_5.txt` | 5 | 10 | 0 | No | Vertex distances | Matches expected | 0.743 us | **Pass** |
| **Bellman-Ford** | `bf_10.txt` | 10 | 15 | 0 | No | Vertex distances | Matches expected | 1.007 us | **Pass** |
| **Bellman-Ford** | `bf_100.txt` | 100 | 516 | 0 | No | Vertex distances | Matches expected | 15.717 us | **Pass** |
| **Bellman-Ford** | `bf_10000.txt` | 10,000 | 29,994 | 0 | No | Vertex distances | Matches expected | 1,008.000 us | **Pass** |
| **Bellman-Ford** | `bf_50000.txt` | 50,000 | 149,994 | 0 | No | Vertex distances | Matches expected | 805.722 us | **Pass** |
| **Bellman-Ford** | `bf_100000.txt` | 100,000 | 299,994 | 0 | No | Vertex distances | Matches expected | 1,001.000 us | **Pass** |
| **Bellman-Ford** | `bf_neg_cycle.txt` | 3 | 3 | 0 | Yes | "Negative cycle: true" | Matches expected | 0.200 us | **Pass** |
| **Floyd-Warshall** | `fw_5.txt` | 5 | N/A | N/A | No | Distance matrix | Matches expected | 3.917 us | **Pass** |
| **Floyd-Warshall** | `fw_10.txt` | 10 | N/A | N/A | No | Distance matrix | Matches expected | 15.057 us | **Pass** |
| **Floyd-Warshall** | `fw_100.txt` | 100 | N/A | N/A | No | Distance matrix | Matches expected | 9,000.000 us | **Pass** |
| **Floyd-Warshall** | `fw_500.txt` | 500 | N/A | N/A | No | Distance matrix | Matches expected | 1,043,130.000 us | **Pass** |
| **Floyd-Warshall** | `fw_neg_cycle.txt`| 3 | N/A | N/A | Yes | "Negative cycle: true" | Matches expected | 1.601 us | **Pass** |

*(Note: Floyd-Warshall scale sizes above $V=500$ (such as $V=1000$ and $V=2000$) take longer due to $O(V^3)$ complexity ($2000^3 = 8 \times 10^9$ operations) and are available in the `tests/` folder for benchmark sweeps. Buddy task algorithms such as Triangle Counting, Betweenness Centrality, and Connected Components are not implemented yet and will be added later.)*

