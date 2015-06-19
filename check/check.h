#include <iostream>
#include <cstring>
#include <fstream>
#include <ctype.h>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

class Check {
	public:
		Check(string file_name);
		int type_check(string a , int b);
		int var_check(string a);
		int keyword_check(string a);
		void start();
		int Check_s(string word);
		int length(string word);
	private:
		   string type[4];
   		string line_save[20];
   		string var_save[20];
   		string type_save[20];
   		string value_save[10];
   		string empty[20];
			
			string file;

   		int order;
   		int type_found;
   		int var_found;

   		int type_num;
   		int var_num;
	   	int value_num;

};
