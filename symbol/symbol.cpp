#include "symbol.h"

Table::Table() {
	scope = 0;
	symbol = "";
	type = "";
	array = false;
	function = false;
}

void Table::Set(int scope_num, string symbol_name, string type_name, bool array, bool function) {
	scope = scope_num;
	symbol = symbol_name;
	type = type_name;
	array = false;
	function = false;
}

int Table::GetScope() {
	return scope;
}

string Table::GetSymbol() {
	return symbol;
}

string Table::GetType() {
	return type;
}

bool Table::GetArray() {
	return array;
}

bool Table::GetFunction() {
	return function;
}

/*-------------------------------------------------------*/

Symbol::Symbol(string file_name) {
	Origin();
	SetFile(file_name);
	SetCount();
}

void Symbol::Origin() {
	file = "";
	count = 0;

	key_word[0] = "int";
	key_word[1] = "char";
	key_word[2] = "float";
	key_word[3] = "double";
}

void Symbol::SetFile(string file_name) {
	file = file_name;
}

string Symbol::GetFile() {
	return file;
}

void Symbol::SetCount() {
	count = 0;
	string line;
	ifstream fin(file.c_str());

	if(fin == NULL) {
		cout << "Can not find \"" << file << "\"." << endl;
	}
	else {
		while(getline(fin, line)) {
			istringstream fin_word(line);
			string word = "";

			while(fin_word >> word) {
				if( FindKeyWord(word) ) {
					count = count + 1;
				}
			}
		}
	}

	fin.close();
}

int Symbol::GetCount() {
	return count;
}

bool Symbol::FindKeyWord(string word) {
	for(int i = 0; i < (sizeof(key_word)/sizeof(*key_word)); i++) {
		if(word == key_word[i]) {
			return true;
		}
	}
	return false;
}
