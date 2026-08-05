CXX = g++
CXXFLAGS = -std=c++17 -Wall

TARGET = gemm

SRC = src/matrix.cpp \
      src/gemm_simple.cpp \
      src/gemm_blocking.cpp \
      src/timer.cpp \
      driver/driver.cpp

INC = -Iinclude

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(INC) -o $(TARGET)

clean:
	del /Q $(TARGET).exe 2>nul || rm -f $(TARGET)

.PHONY: clean
