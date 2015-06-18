#include <iostream>
#include <cstdlib>
#include <fstream>
#include "symbol/symbol.h"
#include "check/check.h"
using namespace std;

void SymbolTable(string file);

int main(int argc, char *argv[]) {
	if(argc == 2) {
		ifstream ft(argv[1]);
		
		
		if(ft != NULL) {
			SymbolTable(argv[1]);

			*------------------------------------------------------*/
			Check check = Check(argv[1]);
			cout << check.GetFile() << endl;
			cout << check.GetScope() << endl;
		}
		else {
			cout << "Can not find \"" << argv[1] << "\"." << endl;
		}

		ft.close();
	}
	else if(argc == 1) {
		cout << "Please input file name." << endl;
	}
	else {
		cout << "Input too much argument." << endl;
	}

	return 0;
}

void SymbolTable(string file) {
	ifstream fp(file.c_str());

	Symbol symbol = Symbol(file);
	Table table[ symbol.GetCount() ];

	fp.close();
}
