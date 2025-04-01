# קומפיילר ודגלים
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# קבצי המקור והאובייקט
SRC = main.cpp graph.cpp algorithms.cpp
OBJ = $(SRC:.cpp=.o)

# שם הקובץ המהודר
TARGET = main

# קומפילציה והרצה
Main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)
	./$(TARGET)

# valgrind לבדוק זיכרון
valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

# ניקוי קבצי ביניים
clean:
	rm -f *.o $(TARGET)