#include <iostream>
#include <cstdlib>
#include <fstream>
#include "symbol/symbol.h"
#include "check/check.h"
using namespace std;

int main(int argc, char *argv[]) {
	if(argc == 2) {
		ifstream ft(argv[1]);

		if(ft != NULL) {
			Symbol symbol = Symbol(argv[1]);
			cout << symbol.GetFile() << endl;
			cout << symbol.GetCount() << endl;

			/*------------------------------------------------------*/

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
