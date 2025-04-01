CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = main
OBJS = main.o graph.o algorithms.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp graph.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

graph.o: graph.cpp graph.hpp
	$(CXX) $(CXXFLAGS) -c graph.cpp

algorithms.o: algorithms.cpp graph.hpp
	$(CXX) $(CXXFLAGS) -c algorithms.cpp

clean:
	rm -f *.o $(TARGET)