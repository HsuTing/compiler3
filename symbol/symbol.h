#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class Symbol {
	public:
		Symbol(string file_name);
		void origin();
		void SetFile(string file_name);
		string GetFile();
		void SetScope();
		int GetScope();
	private:
		string file;
		int scope;
};
