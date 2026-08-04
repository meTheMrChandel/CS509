# Buddy Assignment 01 - Graph Algorithms using CSR

## Course Information

- **Semester:** M.Tech AI - Semester I
- **Institute:** IIT Ropar

---

## Objective

The objective of this assignment is to implement graph traversal and shortest path algorithms using the Compressed Sparse Row (CSR) graph representation.

Implemented algorithms:

- Breadth First Search (BFS)
- Depth First Search (DFS)
- Single Source Shortest Path (Dijkstra)

The graph is first read as an adjacency list and then converted into CSR representation before executing the algorithms.

---

## Project Structure

```
assignment_01/
│
├── driver/
│   └── driver.cpp
│
├── include/
│   ├── graph.h
│   ├── csr.h
│   ├── bfs.h
│   ├── dfs.h
│   ├── sssp.h
│   └── timer.h
│
├── src/
│   ├── graph.cpp
│   ├── csr.cpp
│   ├── bfs.cpp
│   ├── dfs.cpp
│   ├── sssp.cpp
│   └── timer.cpp
│
├── tests/
│
├── outputs/
│
├── Makefile
└── README.md
```

---

## Features

- Graph file reader
- Adjacency List representation
- CSR conversion
- BFS implementation
- DFS implementation
- Dijkstra's Shortest Path
- Execution time measurement

---

## Compilation

```bash
mingw32-make
```

---

## Execution

```bash
./graph_simulator
```

or

```bash
graph_simulator.exe
```

---

## Input Format

### BFS / DFS

```
Number_of_Vertices

Source Destination
Source Destination
...
```

Example

```
5

0 1
0 2
1 3
2 4
```

---

### Dijkstra (Weighted Graph)

```
Number_of_Vertices

Source Destination Weight
Source Destination Weight
...
```

Example

```
5

0 1 10
0 2 5
2 1 3
1 3 2
2 4 7
4 3 1
```

---

## Available Algorithms

```
1. Breadth First Search (BFS)

2. Depth First Search (DFS)

3. Single Source Shortest Path (Dijkstra)
```

---

## Output

The program displays:

- Traversal Order (BFS/DFS)
- Shortest Distance from Source (SSSP)
- Algorithm Execution Time

---

## Performance Measurement

Execution time is measured using the C++ Chrono Library.

The time required to convert the graph from adjacency list to CSR is **not included** in the execution time.

---

## Technologies Used

- C++17
- STL
- Queue
- Priority Queue
- Chrono Library
- Makefile

---

## Author

Vishal Chandel

M.Tech Artificial Intelligence

IIT Ropar