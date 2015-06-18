#include <iostream>
#include <cstring>
#include <fstream>
#include <ctype.h>
#include <memory.h>

using namespace std;

class Check {
	public:
		Check(string file_name);
		int type_check(string a , string b[]);
		int var_check(string a , string b[]);
		void start();
	private:
		   string type[4];
   		string line_save[10];
   		string var_save[20];
   		string type_save[20];
   		string value_save[10];
   		string empty[10];
			
   		string line;
   		string word;
			string file;

   		int order;
   		int type_found;
   		int var_found;

   		int type_num;
   		int var_num;
	   	int value_num;

};
