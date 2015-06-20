#include "llvm.h"

Llvm::Llvm() {
	ifstream fin("data/tree.txt");

	string line = "";
	while(getline(fin, line)) {
		istringstream fin_word(line);
		string word = "";

		while(fin_word >> word) {
			cout << word << " ";
		}
		cout << endl;
	}

	fin.close();
}
