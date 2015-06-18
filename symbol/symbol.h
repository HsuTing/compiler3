#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;

class Symbol {
	public:
		Symbol(string file_name);
		void origin();
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
