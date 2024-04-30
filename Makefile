

all : test

affichage.o: affichage.cpp affichage.cpp
	g++ -std=c++11 -Wall -c affichage.cpp

coord.o: coord.cpp coord.hpp 
	g++ -std=c++11 -Wall -c coord.cpp

fourmis.o: fourmis.hpp fourmis.cpp
	g++ -std=c++11 -Wall -c fourmis.cpp
grilles.o : grilles.hpp grilles.cpp
	g++ -std=c++11 -Wall -c grilles.cpp
test : test.o coord.o fourmis.o grilles.o affichage.o
	g++ -o test test.o coord.o fourmis.o grilles.o affichage.o

test.o: test.cpp doctest.h 
	g++ -std=c++11 -Wall -c test.cpp

check: test
	./test 



clean:
	rm -f *.o coord test