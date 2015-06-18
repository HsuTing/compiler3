#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;

class Table {
	public:
		Table();
		void Set(int scope_num, string symbol_name, string type_name, bool array, bool function);
		int GetScope();
		string GetSymbol();
		string GetType();
		bool GetArray();
		bool GetFunction();
	private:
		int scope;
		string symbol;
		string type;
		bool array;
		bool function;
};

class Symbol {
	public:
		Symbol(string file_name);
		void Origin();
		void SetFile(string file_name);
		string GetFile();
		void SetCount();
		int GetCount();
		bool FindKeyWord(string word);
	private:
		string key_word[4];
		string file;
		int count;
};
