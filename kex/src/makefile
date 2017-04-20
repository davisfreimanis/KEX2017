CC = g++
FLAGS = -pedantic -Wall -std=c++11 -g

main.out: main.cpp orthant_scan.o point.o
	$(CC) $(FLAGS) $^ -o $@
	./main.out

point.o: point.cpp
	$(CC) $(FLAGS) -c $^

orthant_scan.o: orthant_scan.cpp
	$(CC) $(FLAGS) -c $^

%.out: %.cpp
	$(CC) $(FLAGS) $*.cpp -o $*.out

test:
	./cxxtestgen.py --error-printer -o testrunner.cpp convex.cxxtest.cpp
	$(CC) -std=c++11 -c -o point.o point.cpp
	$(CC) -std=c++11 -c -o orthant_scan.o orthant_scan.cpp
	$(CC) -std=c++11 -o convex_test.out -I ../tests/cxxtest/ testrunner.cpp point.o orthant_scan.o
	./convex_test.out

clean:
	rm -f *.o *.out
