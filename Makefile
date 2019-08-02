cc = g++
files = input.h preprocessing.h core_processing.h output.h
os = input.o preprocessing.o core_processing.o output.o

all: main

input.o: input.cpp $(files)
	$(cc) input.cpp -o input.o -c -std=c++11

preprocessing.o: preprocessing.cpp $(files)
	$(cc) preprocessing.cpp -o preprocessing.o -c -std=c++11

core_processing.o: core_processing.cpp $(files)
	$(cc) core_processing.cpp -o core_processing.o -c -std=c++11

output.o: output.cpp $(files)
	$(cc) output.cpp -o output.o -c -std=c++11

main: main.cpp $(files) $(os)
	$(cc) main.cpp $(os) -o main -std=c++11

clear:
	rm -f $(os) main