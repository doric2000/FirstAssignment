CXX = g++
CXXFLAGS = -std=c++11 -Wall
OBJS = main.o graph.o algorithms.o priority_queue.o stack.o queue.o
TARGET = Main

# הפקודה הראשית - קומפילציה והרצה של Main
Main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	./$(TARGET)

# בדיקת זליגת זיכרון
valgrind: Main
	valgrind --leak-check=full ./$(TARGET)

# ניקוי קבצים זמניים
clean:
	rm -f *.o $(TARGET)