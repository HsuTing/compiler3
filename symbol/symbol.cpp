#include "symbol.h"

SymbolTable::SymbolTable(string file_name) {
	file = file_name;

	ifstream fin(file.c_str());
	Symbol symbol = Symbol(file);
	Table table[ symbol.GetCount() ];

	string line;
	int count = 0;

	Origin();

	while(getline(fin, line)) {
		istringstream fin_word(line);
		string word = "";
		string remain = "";
		int pos = 0;

		while(fin_word >> word) {
			while(word != "") {
				if((pos = Check(word)) != -1) {
					if(pos != 0) {
						remain = word.substr(pos);
						word = word.substr(0, pos);
					}
					else {
						remain = word.substr(pos + length(word));
						word = word.substr(0, length(word));
					}
				}

				cout << word << endl;

				pos = 0;
				word = remain;
				remain = "";
			}
		}
	}

	for(int i = 0; i < (sizeof(table)/sizeof(*table)); i++) {
		cout << table[i].GetScope() << " ";
		cout << table[i].GetSymbol() << " ";
		cout << table[i].GetType() << " ";
		cout << (table[i].GetArray() ? "true" : "false") << " ";
		cout << (table[i].GetFunction() ? "true" : "false") << " ";
		cout << endl;
	}

	fin.close();
}

void SymbolTable::Origin() {
	scope = 0;

	key_word[0] = "int";
	key_word[1] = "char";
	key_word[2] = "float";
	key_word[3] = "double";
}

bool SymbolTable::FindKeyWord(string word) {
	for(int i = 0; i < (sizeof(key_word)/sizeof(*key_word)); i++) {
		if(word == key_word[i]) {
			return true;
		}
	}
	return false;
}

int SymbolTable::Check(string word) {
	string temp[] = {"{", "}", "[", "]", "(", ")", ";", ",", "=", "!", "+", "-", "*", "/", "==", "!=", "<", ">", "<=", ">=", "&&", "||"};
	int count = -1;

	for(int i = 0; i < (sizeof(temp) / sizeof(temp[0])); i++) {
		if(word.find(temp[i]) != -1 && count > word.find(temp[i])) {
			count = word.find(temp[i]);
		}
	}

	return count;
}

int SymbolTable::length(string word) {
	string temp[] = {"==", "!=", "<=", ">=", "&&", "||"};
	int count = -1;

	for(int i = 0; i < (sizeof(temp) / sizeof(temp[0])); i++) {
		if(word.find(temp[i]) != -1 && count > word.find(temp[i])) {
			count = word.find(temp[i]);
		}
	}

	if(count != -1) {
		return 2;
	}
	else {
		return 1;
	}
}

/*--------------------------------------------------------*/

Table::Table() {
	Origin();
}

void Table::Origin() {
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
