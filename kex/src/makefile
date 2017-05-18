CC = g++
GNUPLOT = gnuplot
FLAGS = -pedantic -Wall -std=c++11 -g -fopenmp -lpthread
PFLAGS = -fopenmp -lpthread

main.out: main.cpp orthant_scan.o point.o graham_scan.o
	$(CC) $(FLAGS) $^ -o $@

point.o: point.cpp
	$(CC) $(FLAGS) -c $^

orthant_scan.o: orthant_scan.cpp
	$(CC) $(FLAGS) -c $^

graham_scan.o: graham_scan.cpp
	$(CC) $(FLAGS) -c $^

%.out: %.cpp
	$(CC) $(FLAGS) $*.cpp -o $*.out

test:
	./cxxtestgen.py --error-printer -o testrunner.cpp convex.cxxtest.cpp
	$(CC) -std=c++11 -c -o point.o point.cpp
	$(CC) -std=c++11 -c -o orthant_scan.o orthant_scan.cpp
	$(CC) -std=c++11 -c -o graham_scan.o graham_scan.cpp
	$(CC) -std=c++11 -o convex_test.out -I ../tests/cxxtest/ testrunner.cpp point.o orthant_scan.o graham_scan.o
	./convex_test.out

points: points.p points.dat extreme.dat hull.dat fhull.dat outer.dat
	$(GNUPLOT) $<

generate:
	./rbox D2 5000 > points_1000.dat
	./main.out < data_random.txt

clean:
	rm -f *.o *.out
