# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall

# Target executable
TARGET = main

# Source files
SRCS = main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# SFML libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Rule to link the object files and create the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

# Rule to compile the source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(OBJS) $(TARGET)