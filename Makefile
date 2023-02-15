#MAKEFILE

CXXFLAGS: -std=c++11 -g -Wall -Wno -uninitialized

all: tests
	./tests

tests: intbst.cpp testbst.cpp
	g++ $(CXXFLAGS) intbst.cpp testbst.cpp -o tests

clean:
	rm tests