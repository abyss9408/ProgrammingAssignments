# Compiler settings
CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -std=c11
CXXFLAGS = -Wall -Wextra -std=c++11

# Source files
DRIVER_C = driver.c
DRIVER_CPP = driver.cpp
SPLITTER_C = splitter.c
SPLITTER_CPP = splitter.cpp

# Object files
DRIVER_C_OBJ = driver_c.o
DRIVER_CPP_OBJ = driver_cpp.o
SPLITTER_C_OBJ = splitter_c.o
SPLITTER_CPP_OBJ = splitter_cpp.o

# Executables
SJ1_OUT = sj1.out
SJ2_OUT = sj2.out
SJ3_OUT = sj3.out
SJ4_OUT = sj4.out

# Default target
all: $(SJ1_OUT) $(SJ2_OUT) $(SJ3_OUT) $(SJ4_OUT)

# 1. C executable: C driver + C splitter
$(SJ1_OUT): $(DRIVER_C_OBJ) $(SPLITTER_C_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# 2. C++ executable: C++ driver + C++ splitter
$(SJ2_OUT): $(DRIVER_CPP_OBJ) $(SPLITTER_CPP_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# 3. C++ executable: C++ driver + C splitter
$(SJ3_OUT): $(DRIVER_CPP_OBJ) $(SPLITTER_C_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# 4. C++ executable: C++ driver + C++ compiled splitter.c
$(SJ4_OUT): $(DRIVER_CPP_OBJ) splitter_c_as_cpp.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilation rules
$(DRIVER_C_OBJ): $(DRIVER_C)
	$(CC) $(CFLAGS) -c $< -o $@

$(DRIVER_CPP_OBJ): $(DRIVER_CPP)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(SPLITTER_C_OBJ): $(SPLITTER_C)
	$(CC) $(CFLAGS) -c $< -o $@

$(SPLITTER_CPP_OBJ): $(SPLITTER_CPP)
	$(CXX) $(CXXFLAGS) -c $< -o $@

splitter_c_as_cpp.o: $(SPLITTER_C)
	$(CXX) $(CXXFLAGS) -x c++ -c $< -o $@

# Clean target
clean:
	rm -f *.o $(SJ1_OUT) $(SJ2_OUT) $(SJ3_OUT) $(SJ4_OUT)

# Phony targets
.PHONY: all clean