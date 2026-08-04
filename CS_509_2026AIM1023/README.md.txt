# Assignment 01 - GEMM Simulator

## Course Information

- **Course:** CS509 - Parallel Computer Architecture
- **Semester:** M.Tech AI - Semester I
- **Institute:** IIT Ropar

---

## Objective

The objective of this assignment is to implement and compare different General Matrix Multiplication (GEMM) algorithms.

Implemented algorithms:

- Simple GEMM
- Blocking (Tiled) GEMM

Execution time is measured for performance comparison.

---

## Project Structure

```
assignment_01/
│
├── driver/
│   └── driver.cpp
│
├── include/
│   ├── gemm.h
│   ├── matrix.h
│   └── timer.h
│
├── src/
│   ├── gemm_simple.cpp
│   ├── gemm_blocking.cpp
│   ├── matrix.cpp
│   └── timer.cpp
│
├── tests/
│   └── gemm_test_01.txt
│
├── utils/
│
├── outputs/
│
├── Makefile
└── README.md
```

---

## Features

- Matrix file reader
- Simple GEMM implementation
- Blocking GEMM implementation
- Execution time measurement
- Dynamic matrix allocation

---

## Compilation

```bash
mingw32-make
```

---

## Execution

```bash
./gemm
```

or

```bash
gemm.exe
```

---

## Input Format

```
M K N

Matrix A (M × K)

Matrix B (K × N)
```

Example

```
2 2 2

1 2
3 4

5 6
7 8
```

---

## Algorithm Selection

```
1. Simple GEMM
2. Blocking GEMM
```

---

## Output

- Result Matrix
- Execution Time

---

## Performance

Execution time is measured using C++ Chrono Library.

CSR conversion is not applicable in this assignment.

---

## Technologies Used

- C++17
- STL
- Makefile
- MinGW GCC

---

## Author

Vishal Chandel
M.Tech Artificial Intelligence
IIT Ropar