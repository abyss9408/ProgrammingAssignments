CXX = g++
CXXFLAGS = -std=c++23 -Wall
TARGET = quicksort_median_of_medians.out
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

run: $(TARGET)
	@if [ -z "$(FILE)" ]; then \
		echo "Error: Please specify a file name with FILE=<filename>"; \
		exit 1; \
	fi
	./$(TARGET) $(FILE)

clean:
	rm -f $(TARGET) $(OBJS)