CXX = g++
CXXFLAGS = -std=c++17 -Wall

TARGET = shortest_path

SRC = src/csr.cpp \
      src/timer.cpp \
      src/graph_io.cpp \
      src/bellman_ford.cpp \
      src/floyd_warshall.cpp \
      driver/driver.cpp

INC = -Iinclude

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(INC) -o $(TARGET)

clean:
	del /Q $(TARGET).exe 2>nul || rm -f $(TARGET)

.PHONY: clean
