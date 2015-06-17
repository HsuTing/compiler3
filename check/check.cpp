#include "check.h"

Check::Check(string file_name) {
	origin();
	SetFile(file_name);
	SetScope();
}

void Check::origin() {
	file = "";
	scope = 0;
}

void Check::SetFile(string file_name) {
	file = file_name;
}

string Check::GetFile() {
	return file;
}

void Check::SetScope() {
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

int Check::GetScope() {
	return scope;
}
