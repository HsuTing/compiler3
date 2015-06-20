#include "symbol.h"

SymbolTable::SymbolTable(string file_name) {
	file = file_name;

	ifstream fin(file.c_str());
	ofstream fout("data/symbol_table.txt");
	Symbol symbol = Symbol(file);
	Table table[ symbol.GetCount() ];

	string line;
	int count = 0;
	int level_max = 0;
	/*------temp save for table------*/
	int level = 0;
	string symbol_name = "";
	string type_name = "";
	bool array_bool = false;
	bool function_bool = false;

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

				/*-----save in table------*/
				if( FindKeyWord(word) ) {
					type_name = word;
				}
				else {
					if(type_name != "") {
						if(word == ";" || word == "," || word == ")" || word == "(" || word == "[") {
							if(word == ";" || word == "," || word == ")") {
								array_bool = false;
								function_bool = false;
							}
							else if(word == "(") {
								level = 0;
								array_bool = false;
								function_bool = true;
							}
							else if(word == "[") {
								array_bool = true;
								function_bool = false;
							}

							table[count].Set(level, symbol_name, type_name, array_bool, function_bool);
							count = count + 1;
							type_name = "";
						}
						else {
							symbol_name = word;
						}
					}
				}

				if(word == "{" || word == "(") {
					level = level + 1;
				}
				else if(word == ")") {
					level = level - 1;
				}

				if(level > level_max) {
					level_max = level;
				}
				/*------------------------*/

				pos = 0;
				word = remain;
				remain = "";
			}
		}
	}

	int level_temp = 0;
	while(level_temp <= level_max) {
		for(int i = 0; i < (sizeof(table)/sizeof(*table)); i++) {
			if(table[i].GetLevel() == level_temp) {
				if(table[i].GetLevel() == table[i - 1].GetLevel() + 1) {
					scope = scope + 1;
				}
					table[i].SetScope(scope);
			}
		}

		level_temp = level_temp + 1;
	}

	//sort table
	for(int i = 0; i < (sizeof(table)/sizeof(*table)); i++) {
		for(int j = i + 1; j < (sizeof(table)/sizeof(*table)); j++) {
			if(table[j].GetScope() < table[i].GetScope()) {
				Table temp = Table();
				temp.Set(table[j].GetLevel(), table[j].GetSymbol(), table[j].GetType(), table[j].GetArray(), table[j].GetFunction());
				temp.SetScope(table[j].GetScope());

				for(int k = j; k >= i + 1; k--) {
					table[k].Set(table[k - 1].GetLevel(), table[k - 1].GetSymbol(), table[k - 1].GetType(), table[k - 1].GetArray(), table[k - 1].GetFunction());
					table[k].SetScope(table[k - 1].GetScope());
				}

				table[i].Set(temp.GetLevel(), temp.GetSymbol(), temp.GetType(), temp.GetArray(), temp.GetFunction());
				table[i].SetScope(temp.GetScope());
			}
		}
	}

	int temp = 0;
	for(int i = 0; i < (sizeof(table)/sizeof(*table)); i++) {
		if(temp != table[i].GetScope()) {
			temp = table[i].GetScope();
			fout << endl;
		}

		fout << table[i].GetScope() << " ";
		fout << table[i].GetSymbol() << " ";
		fout << table[i].GetType() << " ";
		fout << (table[i].GetArray() ? "true" : "false") << " ";
		fout << (table[i].GetFunction() ? "true" : "false") << " ";
		fout << endl;
	}

	fin.close();
	fout.close();
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
	level = 0;
	symbol = "";
	type = "";
	array = false;
	function = false;
}

void Table::Set(int level_num, string symbol_name, string type_name, bool array_bool, bool function_bool) {
	level = level_num;
	symbol = symbol_name;
	type = type_name;
	array = array_bool;
	function = function_bool;
}

void Table::SetScope(int scope_num) {
	scope = scope_num;
}

int Table::GetScope() {
	return scope;
}

int Table::GetLevel() {
	return level;
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

					if(FindKeyWord(word)) {
						count = count + 1;
					}

					pos = 0;
					word = remain;
					remain = "";
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

int Symbol::Check(string word) {
	string temp[] = {"{", "}", "[", "]", "(", ")", ";", ",", "=", "!", "+", "-", "*", "/", "==", "!=", "<", ">", "<=", ">=", "&&", "||"};
	int count = -1;

	for(int i = 0; i < (sizeof(temp) / sizeof(temp[0])); i++) {
		if(word.find(temp[i]) != -1 && count > word.find(temp[i])) {
			count = word.find(temp[i]);
		}
	}

	return count;
}

int Symbol::length(string word) {
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
