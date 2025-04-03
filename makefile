#dor.cohen15@msmail.ariel.ac.il

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Source files for main program
SRC = main.cpp graph.cpp algorithms.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = main

# Source files for tests
TEST_SRC = test.cpp graph.cpp algorithms.cpp
TEST_BIN = test

# Rule: build the main program (without running it)
Main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Rule: run the main program
run: Main
	./$(TARGET)

# Rule: compile and run tests
test: $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -I. -o $(TEST_BIN) $(TEST_SRC)
	./$(TEST_BIN)

# Rule: check memory leaks with valgrind
valgrind: Main
	valgrind --leak-check=full ./$(TARGET)

# Rule: clean up all build files
clean:
	rm -f *.o $(TARGET) $(TEST_BIN)