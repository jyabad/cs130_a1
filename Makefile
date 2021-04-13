CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field
main: main.o
	$(CXX) $(CXXFLAGS) $^ -o $@
test: main.o
	./main