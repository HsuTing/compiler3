main: main.o symbol.o check.o
	g++ -o hw3 main.o symbol.o check.o

check.o: check/check.cpp check/check.h
	g++ -c check/check.cpp

symbol.o: symbol/symbol.cpp symbol/symbol.h
	g++ -c symbol/symbol.cpp

main.o: main.cpp symbol/symbol.h check/check.h
	g++ -c main.cpp

clean:
	rm symbol *.o check *.o
