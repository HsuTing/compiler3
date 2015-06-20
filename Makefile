hw2: parser_1.o
	g++ -o hw2 parser_1.o
	rm *.o

parser_1.o: parser/parser_1.cpp
	g++ -c parser/parser_1.cpp

hw3: hw3.o symbol.o check.o llvm.o
	g++ -o hw3 hw3.o symbol.o check.o llvm.o
	rm *.o

llvm.o: llvm/llvm.cpp llvm/llvm.h
	g++ -c llvm/llvm.cpp

check.o: check/check.cpp check/check.h
	g++ -c check/check.cpp

symbol.o: symbol/symbol.cpp symbol/symbol.h
	g++ -c symbol/symbol.cpp

hw3.o: hw3.cpp symbol/symbol.h check/check.h llvm/llvm.h
	g++ -c hw3.cpp

clean:
	rm *.o
