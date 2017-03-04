CC = g++
FLAGS = -pedantic -Wall -std=c++11 -g

main.out: graham_scan.cpp point.o
	$(CC) $(FLAGS) $^ -o $@
	./main.out

point.o: point.cpp
	$(CC) $(FLAGS) -c $^

%.out: %.cpp
	$(CC) $(FLAGS) $*.cpp -o $*.out

clean:
	rm -f *.o *.out
