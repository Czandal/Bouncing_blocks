# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++20
# Libraries
LIBS = -lSDL2 -lSDL2_ttf
# Source files
SRCS = main.cpp global.cpp Block.cpp SDL2_framerate.c
# Object files
OBJS = $(SRCS:.cpp=.o)

# Target executable
TARGET = my_project

# Default rule to compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Default rule to compile .c to .o
%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Target to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

# Rule to clean up the project
clean:
	rm -f $(OBJS) $(TARGET)

