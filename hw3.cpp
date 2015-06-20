#include <iostream>
#include <cstdlib>
#include <fstream>
#include "symbol/symbol.h"
#include "check/check.h"
#include "llvm/llvm.h"
using namespace std;

int main(int argc, char *argv[]) {
	if(argc == 2) {
		ifstream ft(argv[1]);

		if(ft != NULL) {
			SymbolTable symbol = SymbolTable(argv[1]);	
			Check a = Check(argv[1]);
<<<<<<< HEAD
			a.create_array();
			a.type_checking();
=======
			a.start();

			Llvm llvm = Llvm();
>>>>>>> 87cc4ada56531315fd77bbbcd1f83e86093a256a
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
