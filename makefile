CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = amazon_tracking
OBJS = main.o testeautomatizado.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

main.o: main.cpp avltree.hpp rubronegro.hpp testeautomatizado.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

testeautomatizado.o: testeautomatizado.cpp testeautomatizado.hpp avltree.hpp rubronegro.hpp
	$(CXX) $(CXXFLAGS) -c testeautomatizado.cpp

clean:
	rm -f *.o $(TARGET)