# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Libraries
LIBS = -lpthread

# Source files
SRCS = main.cpp Bounded_Buffer.cpp Ceditor.cpp Dispatcher.cpp Producer.cpp Smanager.cpp Config.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = ex3.out

# Targets
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC) $(LIBS)

# Rule to compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean command
clean:
	rm -f $(OBJS) $(EXEC)
