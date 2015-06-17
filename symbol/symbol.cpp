#include "symbol.h"

Symbol::Symbol(string file_name) {
	origin();
	SetFile(file_name);
	SetScope();
}

void Symbol::origin() {
	file = "";
	scope = 0;
}

void Symbol::SetFile(string file_name) {
	file = file_name;
}

string Symbol::GetFile() {
	return file;
}

void Symbol::SetScope() {
	scope = 0;
	string line;
	ifstream fin(file.c_str());

	if(fin == NULL) {
		cout << "Can not find \"" << file << "\"." << endl;
	}
	else {
		scope = scope + 1;
		while(getline(fin, line)) {
			if(line.find("{") != -1)
				scope = scope + 1;
		}
	}

	fin.close();
}

int Symbol::GetScope() {
	return scope;
}
