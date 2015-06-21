#include "llvm.h"

Llvm::Llvm() {
	Origin();
	SetCount();

	ifstream ftree("data/tree.txt");
	ifstream ftable("data/symbol_table.txt");
	llTable table[count];

	//add table
	string line = "";
	int line_count = 0;
	while(getline(ftable, line)) {
		if(line == "") {
			continue;
		}

		istringstream fin_word(line);
		string word = "";
		int word_count = 0;
		//set information
		string scope = "";
		string symbol = "";
		string type = "";
		string array = "";
		string function = "";

		while(fin_word >> word) {
			switch(word_count) {
				case 0:
					scope = word;
					break;
				case 1:
					symbol = word; 
					break;
				case 2:
					type = word;
					break;
				case 3:
					array = word;
					break;
				case 4:
					function = word;
					break;
			}
			word_count = word_count + 1;
		}

		table[line_count].Set(scope, symbol, type, array, function);
		line_count = line_count + 1;
	}

	int count_type = 0;
	//add tree
	line = "";
	while(getline(ftree, line)) {
		istringstream fin_word(line);
		string word = "";
		int word_count = 0;

		while(fin_word >> word) {
			word_count = word_count + 1;

			if(word_count == 2) {
				//transform
				if(word == "type") {
					type(table[count_type].GetScope());
				}
				//transform
			}
		}
	}

	for(int i = 0; i < (sizeof(table)/sizeof(*table)); i++) {
		cout << table[i].GetScope() << " ";
		cout << table[i].GetSymbol() << " ";
		cout << table[i].GetType() << " ";
		cout << table[i].GetArray() << " ";
		cout << table[i].GetFunction() << " ";
		cout << endl;
	}

	ftree.close();
	ftable.close();
}

void Llvm::Origin() {
	count = 0;
}

void Llvm::SetCount() {
	ifstream fin("data/symbol_table.txt");

	string line = "";
	while(getline(fin, line)) {
		if(line == "") {
			continue;
		}

		count = count + 1;
	}

	fin.close();
}

void type(string scope) {
}

/*--------------------------------------------------------*/

llTable::llTable() {
	Origin();
}

void llTable::Origin() {
	scope = "";
	symbol = "";
	type = "";
	array = "";
	function = "";
}

void llTable::Set(string scope_num, string symbol_name, string type_name, string array_bool, string function_bool) {
	scope = scope_num;
	symbol = symbol_name;
	type = type_name;
	array = array_bool;
	function = function_bool;
}

string llTable::GetScope() {
	return scope;
}

string llTable::GetSymbol() {
	return symbol;
}

string llTable::GetType() {
	return type;
}

string llTable::GetArray() {
	return array;
}

string llTable::GetFunction() {
	return function;
}
