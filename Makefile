
all : main

main : main.o coord.o fourmis.o grilles.o affichage.o
	g++ -o main main.o coord.o fourmis.o grilles.o affichage.o


main.o : main.cpp 
	g++ -std=c++11 -Wall -c main.cpp
affichage.o: affichage.hpp affichage.cpp
	g++ -std=c++11 -Wall -c affichage.cpp

coord.o: coord.cpp coord.hpp 
	g++ -std=c++11 -Wall -c coord.cpp

fourmis.o: fourmis.hpp fourmis.cpp
	g++ -std=c++11 -Wall -c fourmis.cpp
grilles.o : grilles.hpp grilles.cpp
	g++ -std=c++11 -Wall -c grilles.cpp

test.o: test.cpp doctest.h 
	g++ -std=c++11 -Wall -c test.cpp

check: main
	./main 

clean:
	rm -f *.o coord test grilles fourmis affi