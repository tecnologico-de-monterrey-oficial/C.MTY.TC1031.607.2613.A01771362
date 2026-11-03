CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

all: app tests node pointer

app: main.cpp LinkedList.h Node.h
	$(CXX) $(CXXFLAGS) main.cpp -o app

tests: tests.cpp LinkedList.h Node.h
	$(CXX) $(CXXFLAGS) tests.cpp -o tests_runner

node: test_node.cpp Node.h
	$(CXX) $(CXXFLAGS) test_node.cpp -o test_node

pointer: pointer.cpp Fraction.h
	$(CXX) $(CXXFLAGS) pointer.cpp -o pointer

check: tests
	./tests_runner

clean:
	rm -f app tests_runner test_node pointer

.PHONY: all tests node pointer check clean
