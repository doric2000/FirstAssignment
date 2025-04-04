# dor.cohen15@msmail.ariel.ac.il

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

#always run! those are no real files ..
.PHONY: Main test valgrind clean

# Rule: build and run the main demo
Main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)
	./$(TARGET)

# Rule: build and run unit tests
test: $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -I. -o $(TEST_BIN) $(TEST_SRC)
	./$(TEST_BIN)

# Rule: check for memory leaks with valgrind
valgrind: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)
	valgrind --leak-check=full ./$(TARGET)

# Rule: remove all generated files
clean:
	rm -f *.o $(TARGET) $(TEST_BIN)
