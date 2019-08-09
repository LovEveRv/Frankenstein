cc = g++
files = input.h preprocessing.h core_processing.h output.h controller.h neighbor_search.h point.h sparse_bitset.h
os = input.o preprocessing.o core_processing.o output.o controller.o neighbor_search.o point.o sparse_bitset.o
arg = -std=c++11 -O2

all: main

input.o: input.cpp $(files)
	$(cc) input.cpp -o input.o -c $(arg)

preprocessing.o: preprocessing.cpp $(files)
	$(cc) preprocessing.cpp -o preprocessing.o -c $(arg)

core_processing.o: core_processing.cpp $(files)
	$(cc) core_processing.cpp -o core_processing.o -c $(arg)

output.o: output.cpp $(files)
	$(cc) output.cpp -o output.o -c $(arg)

controller.o: controller.cpp $(files)
	$(cc) controller.cpp -o controller.o -c $(arg)

neighbor_search.o: neighbor_search.cpp $(files)
	$(cc) neighbor_search.cpp -o neighbor_search.o -c $(arg)

point.o: point.cpp $(files)
	$(cc) point.cpp -o point.o -c $(arg)

sparse_bitset.o: sparse_bitset.cpp $(files)
	$(cc) sparse_bitset.cpp -o sparse_bitset.o -c $(arg)

main: main.cpp $(files) $(os)
	$(cc) main.cpp $(os) -o main $(arg)

clear:
	rm -f $(os) main