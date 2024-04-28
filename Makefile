

all : test


coord.o: coord.cpp coord.hpp 
	g++ -std=c++11 -Wall -c coord.cpp

test : test.o coord.o
	g++ -o test test.o coord.o

test.o: test.cpp doctest.h 
	g++ -std=c++11 -Wall -c test.cpp

check: test
	./test 



clean:
	rm -f *.o coord test