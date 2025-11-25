CXX = g++
CXXFLAGS = -std=c++23 -Wall
TARGET = convex_hull.out
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
	./$(TARGET) $(FILE)

clean:
	rm -f $(TARGET) $(OBJS)