CXX = g++
CXXFLAGS = -std=c++23 -Wall
TARGET = solution 
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
DEPS = $(wildcard *.h)

default: $(TARGET)

# Rule to build object files
%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

.PHONY: clean run

# linux/mac: ./solution ./test_case.txt  
run: $(TARGET)
	./$(TARGET) ./test_case.txt

# windows: .\solution .\test_case.txt
run_2: $(TARGET)
	.\$(TARGET) .\test_case.txt

# linux/mac
clean:
	rm -f $(TARGET) $(OBJS) 

# windows
clean_2:
	del /f /q $(TARGET) $(OBJS) 