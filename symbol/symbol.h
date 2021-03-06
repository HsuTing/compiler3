#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;

class SymbolTable {
	public:
		SymbolTable(string file_name);
	private:
		string key_word[4]; //type
		string file; //fuke name
		int scope;

		void Origin();
		bool FindKeyWord(string word); //find if keyword is im line
		int Check(string word);	// use to cut line to keyword
		int length(string word); // use to cut line to keyword
};

class Table {
	public:
		Table();
		void Set(int level_num, string symbol_name, string type_name, bool array, bool function);
		void SetScope(int scope_num);
		int GetScope();
		int GetLevel();
		string GetSymbol();
		string GetType();
		bool GetArray();
		bool GetFunction();
	private:
		// Our information
		int scope;
		int level;
		string symbol;
		string type;
		bool array;
		bool function;

		void Origin();
};

class Symbol {
	public:
		Symbol(string file_name);
		string GetFile();
		int GetCount();
	private:
		string key_word[4];
		string file;
		int count; // fund how many type in file

		void Origin();
		void SetFile(string file_name);
		void SetCount();
		bool FindKeyWord(string word);
		int Check(string word);
		int length(string word);
};
