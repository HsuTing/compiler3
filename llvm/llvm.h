#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;

class llTable {
	public:
		llTable();
		void Set(string scope_num, string symbol_name, string type_name, string array, string function);
		string GetScope();
		string GetSymbol();
		string GetType();
		string GetArray();
		string GetFunction();
	private:
		// Our information
		string scope;
		string symbol;
		string type;
		string array;
		string function;

		void Origin();
};

class Llvm {
	public:
		Llvm();
	private:
		int count;

		void Origin();
		void SetCount();
};
