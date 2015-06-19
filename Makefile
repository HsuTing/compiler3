hw3: hw3.o symbol.o check.o
	g++ -o hw3 hw3.o symbol.o check.o

check.o: check/check.cpp check/check.h
	g++ -c check/check.cpp

symbol.o: symbol/symbol.cpp symbol/symbol.h
	g++ -c symbol/symbol.cpp

hw3.o: hw3.cpp symbol/symbol.h check/check.h
	g++ -c hw3.cpp

clean:
	rm symbol *.o check *.o
